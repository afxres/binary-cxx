#ifndef BINARY_EXPERIMENTAL_INTERNAL_DEFINE_HPP
#define BINARY_EXPERIMENTAL_INTERNAL_DEFINE_HPP

#define BINARY_EXPERIMENTAL_DEFINE_STATIC_LENGTH_METHOD() static constexpr size_t Length()
#define BINARY_EXPERIMENTAL_DEFINE_STATIC_ENCODE_METHOD(ARG_OBJECT_TYPE) static void Encode(Allocator& allocator, const ARG_OBJECT_TYPE& item)
#define BINARY_EXPERIMENTAL_DEFINE_STATIC_DECODE_METHOD(ARG_OBJECT_TYPE) static ARG_OBJECT_TYPE Decode(const std::span<const std::byte>& span)
#define BINARY_EXPERIMENTAL_DEFINE_STATIC_ENCODE_WITH_LENGTH_PREFIX_METHOD(ARG_OBJECT_TYPE) static void EncodeWithLengthPrefix(Allocator& allocator, const ARG_OBJECT_TYPE& item)

#define BINARY_EXPERIMENTAL_FORWARD_STATIC_LENGTH_METHOD() \
    BINARY_EXPERIMENTAL_DEFINE_STATIC_LENGTH_METHOD() {    \
        return ConverterType::Length();                    \
    }

#define BINARY_EXPERIMENTAL_FORWARD_STATIC_ENCODE_METHOD()  \
    BINARY_EXPERIMENTAL_DEFINE_STATIC_ENCODE_METHOD(auto) { \
        ConverterType::Encode(allocator, item);             \
    }

#define BINARY_EXPERIMENTAL_FORWARD_STATIC_DECODE_METHOD()  \
    BINARY_EXPERIMENTAL_DEFINE_STATIC_DECODE_METHOD(auto) { \
        return ConverterType::Decode(span);                 \
    }

#define BINARY_EXPERIMENTAL_FORWARD_STATIC_ENCODE_WITH_LENGTH_PREFIX_METHOD()  \
    BINARY_EXPERIMENTAL_DEFINE_STATIC_ENCODE_WITH_LENGTH_PREFIX_METHOD(auto) { \
        ConverterType::EncodeWithLengthPrefix(allocator, item);                \
    }

#include "binary/Allocator.hpp"

namespace binary::experimental {
template <typename T>
struct Converter;
}

#endif
