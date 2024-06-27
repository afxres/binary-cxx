#pragma once

#ifndef BINARY_CONVERTER_HPP
#define BINARY_CONVERTER_HPP

#include <cstddef>
#include <cstdint>
#include <span>

#include "Allocator.hpp"
#include "Define.hpp"
#include "IConverter.hpp"

namespace binary {
template <typename T>
class Converter : public IConverter {
public:
    Converter()
        : IConverter(typeid(T)) {}

    Converter(int32_t length)
        : IConverter(typeid(T), length) {}

    virtual void Encode(Allocator& allocator, const T& item) = 0;

    virtual void EncodeAuto(Allocator& allocator, const T& item) {
        int32_t length = Length();
        if (length != 0) {
            Encode(allocator, item);
        } else {
            EncodeWithLengthPrefix(allocator, item);
        }
    }

    virtual void EncodeWithLengthPrefix(Allocator& allocator, const T& item) {
        int32_t anchor = allocator.Anchor();
        Encode(allocator, item);
        allocator.FinishAnchor(anchor);
    }

    virtual T Decode(const std::span<std::byte> span) = 0;

    virtual T DecodeAuto(std::span<std::byte>& span) {
        int32_t length = Length();
        if (length != 0) {
            T result = Decode(span);
            span = span.subspan(static_cast<size_t>(length));
            return result;
        } else {
            return DecodeWithLengthPrefix(span);
        }
    }

    virtual T DecodeWithLengthPrefix(std::span<std::byte>& span) {
        return Decode(::binary::DecodeWithLengthPrefix(span));
    }
};
}

#endif
