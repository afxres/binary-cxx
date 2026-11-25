#ifndef BINARY_EXPERIMENTAL_CONVERTERS_CONTAINERCONVERTER_HPP
#define BINARY_EXPERIMENTAL_CONVERTERS_CONTAINERCONVERTER_HPP

#include <bit>
#include <concepts>
#include <type_traits>

#include "binary/ConverterExtensions.hpp"
#include "binary/experimental/ConverterDefaults.hpp"
#include "binary/experimental/converters/LittleEndianConverter.hpp"
#include "binary/experimental/helpers/GetConverterHelper.hpp"
#include "binary/experimental/internal/Define.hpp"
#include "binary/internal/ContainerInsertFunction.hpp"
#include "binary/internal/ContainerResizeFunction.hpp"
#include "binary/internal/Exception.hpp"
#include "binary/internal/Length.hpp"
#include "binary/internal/TupleSize.hpp"

namespace binary::experimental::converters {
// A tuple like type is not a container: it is written positionally, with its own
// element boundaries, so treating it as a range yields a wire nothing else reads.
template <typename T>
    requires std::same_as<T, std::remove_cv_t<T>> && (!requires { ::binary::internal::TupleSize<T>::Value; })
struct ContainerConverter : ConverterDefaults<ContainerConverter<T>> {
    using ValueType = std::ranges::range_value_t<T>;
    using ValueConverterType = typename ::binary::experimental::helpers::GetConverterHelper<ValueType>::Type;
    static constexpr bool Contiguous = std::same_as<ValueConverterType, ::binary::experimental::converters::LittleEndianConverter<ValueType>> && std::is_trivially_copyable_v<ValueType> && requires(T& item) { item.data(); item.size(); };
    static constexpr bool Copyable = Contiguous && (sizeof(ValueType) == 1 || std::endian::native == std::endian::little);

    BINARY_EXPERIMENTAL_STATIC_LENGTH_METHOD() {
        return 0;
    }

    BINARY_EXPERIMENTAL_STATIC_ENCODE_METHOD(T) {
        if constexpr (Copyable) {
            allocator.Append(std::span(reinterpret_cast<const std::byte*>(item.data()), sizeof(ValueType) * item.size()));
        } else {
            for (const auto& i : item) {
                ValueConverterType::EncodeAuto(allocator, i);
            }
        }
    }

    BINARY_EXPERIMENTAL_STATIC_ENCODE_WITH_LENGTH_PREFIX_METHOD(T) {
        if constexpr (Copyable) {
            ::binary::EncodeWithLengthPrefix(allocator, std::span(reinterpret_cast<const std::byte*>(item.data()), sizeof(ValueType) * item.size()));
        } else if constexpr (Contiguous) {
            ::binary::Encode(allocator, sizeof(ValueType) * item.size());
            Encode(allocator, item);
        } else if constexpr (std::ranges::sized_range<T> && ValueConverterType::Length() != 0) {
            ::binary::Encode(allocator, ValueConverterType::Length() * static_cast<size_t>(std::ranges::size(item)));
            Encode(allocator, item);
        } else {
            using typename ::binary::internal::AllocatorUnsafeAccessor;
            size_t anchor = AllocatorUnsafeAccessor::Anchor(allocator);
            Encode(allocator, item);
            AllocatorUnsafeAccessor::FinishAnchor(allocator, anchor);
        }
    }

    BINARY_EXPERIMENTAL_STATIC_DECODE_METHOD(T) {
        if constexpr (!::binary::internal::ContainerInsertFunction<T>::IsEnable) {
            ::binary::internal::ThrowNoSuitableEmplaceMethod(typeid(T));
        } else {
            if (span.empty()) {
                return {};
            }
            if constexpr (Copyable) {
                auto capacity = ::binary::internal::GetCapacity(span.size(), sizeof(ValueType), typeid(T));
                auto data = std::span<const ValueType>(reinterpret_cast<const ValueType*>(span.data()), capacity);
                return T(data.begin(), data.end());
            } else {
                T result{};
                std::span<const std::byte> copy = span;
                if constexpr (::binary::internal::ContainerResizeFunction<T>::IsEnable) {
                    if constexpr (ValueConverterType::Length() != 0) {
                        size_t capacity = ::binary::internal::GetCapacity(span.size(), ValueConverterType::Length(), typeid(T));
                        ::binary::internal::ContainerResizeFunction<T>::Invoke(result, capacity);
                    }
                }
                while (!copy.empty()) {
                    ::binary::internal::ContainerInsertFunction<T>::Invoke(result, ValueConverterType::DecodeAuto(copy));
                }
                return result;
            }
        }
    }
};
}

namespace binary::experimental::helpers {
template <typename T>
    requires std::same_as<T, std::remove_cv_t<T>> &&
    std::ranges::input_range<T> && (!requires(const T& item) { item.c_str(); }) &&
    (!requires { ::binary::internal::TupleSize<T>::Value; })
struct GetConverterHelper<T> {
    using Type = ::binary::experimental::converters::ContainerConverter<T>;
};
}

#endif
