#ifndef BINARY_CONVERTERS_LITTLEENDIANCONVERTER_HPP
#define BINARY_CONVERTERS_LITTLEENDIANCONVERTER_HPP

#include <cassert>

#include "binary/Converter.hpp"
#include "binary/internal/Endian.hpp"
#include "binary/internal/Length.hpp"

namespace binary::converters {
template <typename T>
    requires std::same_as<T, std::remove_cv_t<T>>
class LittleEndianConverter : public Converter<T> {
public:
    LittleEndianConverter()
        : Converter<T>(sizeof(T)) {}

    virtual void Encode(Allocator& allocator, const T& item) override {
        allocator.Append(sizeof(T), [item](std::span<std::byte> span) {
            assert(span.size() == sizeof(T));
            internal::EncodeLittleEndian(span.data(), item);
        });
    }

    virtual T Decode(const std::span<const std::byte>& span) override {
        return internal::DecodeLittleEndian<T>(internal::EnsureLength(span, sizeof(T)));
    }
};
}

#endif
