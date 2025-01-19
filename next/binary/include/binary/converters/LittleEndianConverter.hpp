#ifndef BINARY_CONVERTERS_LITTLEENDIANCONVERTER_HPP
#define BINARY_CONVERTERS_LITTLEENDIANCONVERTER_HPP

#include <cassert>

#include "binary/Converter.hpp"
#include "binary/Endian.hpp"

namespace binary::converters {
template <typename T>
class LittleEndianConverter : public Converter<T> {
public:
    LittleEndianConverter()
        : Converter<T>(sizeof(T)) {}

    virtual void Encode(Allocator& allocator, const T& item) override {
        allocator.Append(sizeof(T), [item](std::span<std::byte> span) {
            assert(span.size() == sizeof(T));
            EncodeLittleEndian(span.data(), item);
        });
    }

    virtual T Decode(const std::span<const std::byte>& span) override {
        const std::byte* source = EnsureLength(span, sizeof(T));
        return DecodeLittleEndian<T>(source);
    }
};
}

#endif
