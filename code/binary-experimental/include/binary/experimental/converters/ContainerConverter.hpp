#ifndef BINARY_EXPERIMENTAL_CONVERTERS_CONTAINERCONVERTER_HPP
#define BINARY_EXPERIMENTAL_CONVERTERS_CONTAINERCONVERTER_HPP

#include <concepts>

#include "binary/experimental/helpers/ConverterDecodeAutoMethodHelper.hpp"
#include "binary/experimental/helpers/ConverterEncodeAutoMethodHelper.hpp"
#include "binary/internal/ContainerInsertFunction.hpp"
#include "binary/internal/ContainerResizeFunction.hpp"
#include "binary/internal/Exception.hpp"
#include "binary/internal/Module.hpp"

namespace binary::experimental::converters {
template <typename T>
    requires std::same_as<T, std::remove_cv_t<T>>
struct ContainerConverter {
    using ValueType = std::ranges::range_value_t<T>;
    using ValueConverterType = ::binary::experimental::Converter<ValueType>;

    BINARY_EXPERIMENTAL_DEFINE_STATIC_LENGTH_METHOD() {
        return 0;
    }

    BINARY_EXPERIMENTAL_DEFINE_STATIC_ENCODE_METHOD(T) {
        for (const auto& i : item) {
            ::binary::experimental::helpers::ConverterEncodeAutoMethodHelper<ValueConverterType>::Invoke(allocator, i);
        }
    }

    BINARY_EXPERIMENTAL_DEFINE_STATIC_DECODE_METHOD(T) {
        if constexpr (!::binary::internal::ContainerInsertFunction<T>::IsEnable) {
            ::binary::internal::ThrowNoSuitableEmplaceMethod(typeid(T));
        } else {
            if (span.empty()) {
                return {};
            }
            T result{};
            std::span<const std::byte> copy = span;
            if constexpr (::binary::internal::ContainerResizeFunction<T>::IsEnable) {
                constexpr size_t length = ValueConverterType::Length();
                if constexpr (length != 0) {
                    size_t capacity = ::binary::internal::GetCapacity(span.size(), length, typeid(T));
                    ::binary::internal::ContainerResizeFunction<T>::Invoke(result, capacity);
                }
            }
            while (!copy.empty()) {
                ::binary::internal::ContainerInsertFunction<T>::Invoke(result, ::binary::experimental::helpers::ConverterDecodeAutoMethodHelper<ValueConverterType>::Invoke(copy));
            }
            return result;
        }
    }
};
}

namespace binary::experimental {
template <typename T>
    requires std::same_as<T, std::remove_cv_t<T>> &&
    std::ranges::input_range<T> && (!requires(const T& item) { item.c_str(); })
struct Converter<T> {
    using ObjectType = T;
    using ActualConverterType = ::binary::experimental::converters::ContainerConverter<T>;
    BINARY_EXPERIMENTAL_FORWARD_STATIC_LENGTH_METHOD();
    BINARY_EXPERIMENTAL_FORWARD_STATIC_ENCODE_METHOD();
    BINARY_EXPERIMENTAL_FORWARD_STATIC_DECODE_METHOD();
};
}

#endif
