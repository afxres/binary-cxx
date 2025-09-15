#ifndef BINARY_CONVERTERS_LITTLEENDIANCONVERTER_HPP
#define BINARY_CONVERTERS_LITTLEENDIANCONVERTER_HPP

#include "binary/Converter.hpp"
#include "binary/internal/AllocatorUnsafeAccessor.hpp"
#include "binary/internal/Define.hpp"
#include "binary/internal/Endian.hpp"
#include "binary/internal/Exception.hpp"

namespace binary::converters {
template <typename T>
    requires std::same_as<T, std::remove_cv_t<T>>
class LittleEndianConverter : public Converter<T> {
public:
    LittleEndianConverter()
        : Converter<T>(sizeof(T)) {}

    BINARY_DEFINE_OVERRIDE_ENCODE_METHOD(T) {
        ::binary::internal::EncodeLittleEndian(internal::AllocatorUnsafeAccessor::Assign(allocator, sizeof(T)), item);
    }

    BINARY_DEFINE_OVERRIDE_DECODE_METHOD(T) {
        if (span.size() < sizeof(T)) {
            ::binary::internal::ThrowNotEnoughBytes();
        }
        return ::binary::internal::DecodeLittleEndian<T>(span.data());
    }
};
}

#endif
