#ifndef BINARY_EXPERIMENTAL_CONVERTERS_LITTLEENDIANCONVERTER_HPP
#define BINARY_EXPERIMENTAL_CONVERTERS_LITTLEENDIANCONVERTER_HPP

#include <concepts>

#include "binary/experimental/internal/Define.hpp"
#include "binary/internal/AllocatorUnsafeAccessor.hpp"
#include "binary/internal/Endian.hpp"
#include "binary/internal/Exception.hpp"

namespace binary::experimental::converters {
template <typename T>
    requires std::same_as<T, std::remove_cv_t<T>>
struct LittleEndianConverter {
    BINARY_EXPERIMENTAL_DEFINE_STATIC_LENGTH_METHOD() {
        return sizeof(T);
    }

    BINARY_EXPERIMENTAL_DEFINE_STATIC_ENCODE_METHOD(T) {
        internal::EncodeLittleEndian(internal::AllocatorUnsafeAccessor::Assign(allocator, sizeof(T)), item);
    }

    BINARY_EXPERIMENTAL_DEFINE_STATIC_DECODE_METHOD(T) {
        if (span.size() < sizeof(T)) {
            internal::ThrowNotEnoughBytes();
        }
        return internal::DecodeLittleEndian<T>(span.data());
    }
};
}

namespace binary::experimental {
template <typename T>
    requires std::same_as<T, std::remove_cv_t<T>> &&
    (std::is_integral_v<T> || std::is_floating_point_v<T> || std::is_enum_v<T>)
struct Converter<T> {
    using ConverterType = ::binary::experimental::converters::LittleEndianConverter<T>;
    BINARY_EXPERIMENTAL_FORWARD_STATIC_LENGTH_METHOD();
    BINARY_EXPERIMENTAL_FORWARD_STATIC_ENCODE_METHOD();
    BINARY_EXPERIMENTAL_FORWARD_STATIC_DECODE_METHOD();
};
}

#endif
