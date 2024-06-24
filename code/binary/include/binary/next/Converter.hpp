#pragma once

#ifndef BINARY_CONVERTER_HPP
#define BINARY_CONVERTER_HPP

#include <cstddef>
#include <cstdint>
#include <span>
#include <stdexcept>

#include "Define.hpp"
#include "Endian.hpp"

namespace binary {
class Allocator;

template <typename T>
class Converter {
private:
    int32_t length;

public:
    Converter() {
        this->length = 0;
    }

    Converter(int32_t length) {
        if (length < 0) {
            throw std::out_of_range("length < 0");
        }
        this->length = length;
    }

    int32_t Length() {
        return this->length;
    }

    virtual void Encode(Allocator& allocator, const T& item) = 0;

    virtual void EncodeAuto(Allocator& allocator, const T& item) {
        int32_t length = this->length;
        if (length != 0) {
            Encode(allocator, item);
        } else {
            EncodeWithLengthPrefix(allocator, item);
        }
    }

    virtual void EncodeWithLengthPrefix(Allocator& allocator, const T& item) {
        // TODO: wait for Allocator
    }

    virtual T Decode(const std::span<std::byte> span) = 0;

    virtual T DecodeAuto(std::span<std::byte>& span) {
        int32_t length = this->length;
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
