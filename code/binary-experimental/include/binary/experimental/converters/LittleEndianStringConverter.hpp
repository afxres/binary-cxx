#ifndef BINARY_EXPERIMENTAL_CONVERTERS_LITTLEENDIANSTRINGCONVERTER_HPP
#define BINARY_EXPERIMENTAL_CONVERTERS_LITTLEENDIANSTRINGCONVERTER_HPP

#include <concepts>

#include "binary/experimental/internal/Define.hpp"
#include "binary/internal/Converter.hpp"
#include "binary/internal/Endian.hpp"

namespace binary::experimental::converters {
template <typename T>
    requires std::same_as<T, std::remove_cv_t<T>>
struct LittleEndianStringConverter {
    using ValueType = typename T::value_type;

    BINARY_EXPERIMENTAL_DEFINE_STATIC_LENGTH_METHOD() {
        return 0;
    }

    BINARY_EXPERIMENTAL_DEFINE_STATIC_ENCODE_METHOD(T) {
        if (item.size() == 0) {
            return;
        }
        constexpr size_t size = sizeof(ValueType);
        if constexpr (size == 1) {
            allocator.Append(std::span(reinterpret_cast<const std::byte*>(item.data()), item.size()));
        } else {
            allocator.Append(size * item.size(), [&item](std::span<std::byte> span) {
                assert(span.size() == size * item.size());
                auto target = reinterpret_cast<ValueType*>(span.data());
                auto source = item.data();
                for (size_t i = 0; i < item.size(); i++) {
                    ::binary::internal::EncodeLittleEndian(&target[i], source[i]);
                }
            });
        }
    }

    BINARY_EXPERIMENTAL_DEFINE_STATIC_ENCODE_WITH_LENGTH_PREFIX_METHOD(T) {
        constexpr size_t size = sizeof(ValueType);
        ::binary::Encode(allocator, size * item.size());
        Encode(allocator, item);
    }

    BINARY_EXPERIMENTAL_DEFINE_STATIC_DECODE_METHOD(T) {
        if (span.size() == 0) {
            return {};
        }
        constexpr size_t size = sizeof(ValueType);
        if constexpr (size == 1) {
            return T(reinterpret_cast<const ValueType*>(span.data()), span.size());
        } else {
            T result{};
            auto capacity = ::binary::internal::GetCapacity(span.size(), size, typeid(T));
            result.resize(capacity);
            auto source = reinterpret_cast<const ValueType*>(span.data());
            auto target = result.data();
            for (size_t i = 0; i < result.size(); i++) {
                target[i] = ::binary::internal::DecodeLittleEndian<ValueType>(&source[i]);
            }
            return result;
        }
    }
};
}

namespace binary::experimental {
template <typename T>
    requires std::same_as<T, std::remove_cv_t<T>> &&
    requires { typename T::value_type; } &&
    requires(const T& item) { item.data(); item.size(); item.c_str(); }
struct Converter<T> {
    using ObjectType = T;
    using ActualConverterType = ::binary::experimental::converters::LittleEndianStringConverter<T>;
    BINARY_EXPERIMENTAL_FORWARD_STATIC_LENGTH_METHOD();
    BINARY_EXPERIMENTAL_FORWARD_STATIC_ENCODE_METHOD();
    BINARY_EXPERIMENTAL_FORWARD_STATIC_DECODE_METHOD();
    BINARY_EXPERIMENTAL_FORWARD_STATIC_ENCODE_WITH_LENGTH_PREFIX_METHOD();
};
}

#endif
