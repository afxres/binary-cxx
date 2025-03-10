#ifndef BINARY_CONVERTERS_LITTLEENDIANCONVERTER_HPP
#define BINARY_CONVERTERS_LITTLEENDIANCONVERTER_HPP

#include "binary/Converter.hpp"
#include "binary/internal/AllocatorUnsafeAccessor.hpp"
#include "binary/internal/Endian.hpp"
#include "binary/internal/Exception.hpp"

namespace binary::converters {
template <typename T>
    requires std::same_as<T, std::remove_cv_t<T>>
class LittleEndianConverter : public Converter<T> {
public:
    LittleEndianConverter()
        : Converter<T>(sizeof(T)) {}

    virtual void Encode(Allocator& allocator, const T& item) override {
        internal::EncodeLittleEndian(internal::AllocatorUnsafeAccessor::Assign(allocator, sizeof(T)), item);
    }

    virtual T Decode(const std::span<const std::byte>& span) override {
        if (span.size() < sizeof(T)) {
            internal::ThrowNotEnoughBytes();
        }
        return internal::DecodeLittleEndian<T>(span.data());
    }
};
}

#endif
