#ifndef BINARY_CONVERTERS_LITTLEENDIANSTRINGCONVERTER_HPP
#define BINARY_CONVERTERS_LITTLEENDIANSTRINGCONVERTER_HPP

#include "binary/internal/Define.hpp"
#include "binary/internal/String.hpp"

namespace binary::converters {
template <typename T>
    requires std::same_as<T, std::remove_cv_t<T>>
class LittleEndianStringConverter : public Converter<T> {
public:
    BINARY_DEFINE_OVERRIDE_ENCODE_METHOD(T) {
        ::binary::internal::EncodeLittleEndianString(allocator, item);
    }

    BINARY_DEFINE_OVERRIDE_ENCODE_AUTO_METHOD(T) {
        EncodeWithLengthPrefix(allocator, item);
    }

    BINARY_DEFINE_OVERRIDE_ENCODE_WITH_LENGTH_PREFIX_METHOD(T) {
        constexpr size_t size = sizeof(typename T::value_type);
        ::binary::Encode(allocator, size * item.size());
        ::binary::internal::EncodeLittleEndianString(allocator, item);
    }

    BINARY_DEFINE_OVERRIDE_DECODE_METHOD(T) {
        return ::binary::internal::DecodeLittleEndianString<T>(span);
    }

    BINARY_DEFINE_OVERRIDE_DECODE_AUTO_METHOD(T) {
        return DecodeWithLengthPrefix(span);
    }

    BINARY_DEFINE_OVERRIDE_DECODE_WITH_LENGTH_PREFIX_METHOD(T) {
        return ::binary::internal::DecodeLittleEndianString<T>(::binary::DecodeWithLengthPrefix(span));
    }
};
}

#endif
