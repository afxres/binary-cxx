#ifndef BINARY_EXPERIMENTAL_CONVERTERS_LITTLEENDIANSTRINGCONVERTER_HPP
#define BINARY_EXPERIMENTAL_CONVERTERS_LITTLEENDIANSTRINGCONVERTER_HPP

#include <concepts>

#include "binary/experimental/internal/Define.hpp"
#include "binary/internal/String.hpp"

namespace binary::experimental::converters {
template <typename T>
    requires std::same_as<T, std::remove_cv_t<T>>
struct LittleEndianStringConverter {
    using ValueType = typename T::value_type;

    BINARY_EXPERIMENTAL_DEFINE_STATIC_LENGTH_METHOD() {
        return 0;
    }

    BINARY_EXPERIMENTAL_DEFINE_STATIC_ENCODE_METHOD(T) {
        ::binary::internal::EncodeLittleEndianString(allocator, item);
    }

    BINARY_EXPERIMENTAL_DEFINE_STATIC_ENCODE_WITH_LENGTH_PREFIX_METHOD(T) {
        constexpr size_t size = sizeof(ValueType);
        ::binary::Encode(allocator, size * item.size());
        Encode(allocator, item);
    }

    BINARY_EXPERIMENTAL_DEFINE_STATIC_DECODE_METHOD(T) {
        return ::binary::internal::DecodeLittleEndianString<T>(span);
    }
};
}

namespace binary::experimental {
template <typename T>
    requires std::same_as<T, std::remove_cv_t<T>> &&
    requires { typename T::value_type; } &&
    requires(const T& item) { item.empty(); item.data(); item.size(); item.c_str(); }
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
