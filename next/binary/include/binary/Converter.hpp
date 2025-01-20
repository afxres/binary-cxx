#ifndef BINARY_CONVERTER_HPP
#define BINARY_CONVERTER_HPP

#include <cstddef>
#include <span>

#include "binary/Allocator.hpp"
#include "binary/IConverter.hpp"
#include "binary/Memory.hpp"

namespace binary {
template <typename T>
    requires std::same_as<T, std::remove_cv_t<T>>
class Converter : public IConverter {
public:
    Converter()
        : IConverter(typeid(Converter<T>)) {}

    Converter(size_t length)
        : IConverter(typeid(Converter<T>), length) {}

    virtual void Encode(Allocator& allocator, const T& item) = 0;

    virtual void EncodeAuto(Allocator& allocator, const T& item) {
        size_t length = Length();
        if (length != 0) {
            Encode(allocator, item);
        } else {
            EncodeWithLengthPrefix(allocator, item);
        }
    }

    virtual void EncodeWithLengthPrefix(Allocator& allocator, const T& item) {
        size_t anchor = allocator.Anchor();
        Encode(allocator, item);
        allocator.FinishAnchor(anchor);
    }

    virtual T Decode(const std::span<const std::byte>& span) = 0;

    virtual T DecodeAuto(std::span<const std::byte>& span) {
        size_t length = Length();
        if (length != 0) {
            T result = Decode(span);
            span = span.subspan(length);
            return result;
        } else {
            return DecodeWithLengthPrefix(span);
        }
    }

    virtual T DecodeWithLengthPrefix(std::span<const std::byte>& span) {
        return Decode(::binary::DecodeWithLengthPrefix(span));
    }
};
}

#endif
