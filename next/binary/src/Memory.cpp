#include "binary/Memory.hpp"

#include <cassert>
#include <cstddef>
#include <cstdint>
#include <span>
#include <stdexcept>

#include "binary/Endian.hpp"

namespace binary {
size_t EncodeLengthPrefixLength(const size_t number) {
    assert(number <= INT32_MAX);
    if ((static_cast<uint32_t>(number) >> 7) == 0) {
        return 1;
    } else {
        return 4;
    }
}

size_t DecodeLengthPrefixLength(const std::byte header) {
    if ((static_cast<uint32_t>(header) & 0x80U) == 0) {
        return 1;
    } else {
        return 4;
    }
}

void EncodeLengthPrefix(std::byte* buffer, const size_t number, const size_t length) {
    assert(number <= INT32_MAX);
    assert(length == 1 || length == 4);
    assert(length >= EncodeLengthPrefixLength(number));
    if (length == 1) {
        EncodeBigEndian<uint8_t>(buffer, static_cast<uint8_t>(number));
    } else {
        EncodeBigEndian<uint32_t>(buffer, static_cast<uint32_t>(number) | 0x8000'0000);
    }
}

size_t DecodeLengthPrefix(const std::byte* buffer, size_t& offset, const size_t limits) {
    assert(limits >= offset);
    if (limits == offset) {
        throw std::out_of_range("not enough bytes");
    }
    const std::byte* source = buffer + offset;
    uint32_t header = static_cast<uint32_t>(DecodeBigEndian<uint8_t>(source));
    offset += 1;
    if ((header & 0x80U) == 0) {
        return header;
    }
    assert(limits >= offset);
    if (limits - offset < 3U) {
        throw std::out_of_range("not enough bytes");
    }
    uint32_t result = DecodeBigEndian<uint32_t>(source);
    offset += 3;
    return result & 0x7FFF'FFFU;
}

size_t EnsureLength(const size_t length) {
    if (length > INT32_MAX) {
        throw std::length_error("length overflow");
    }
    return length;
}

const std::byte* EnsureLength(const std::span<const std::byte>& span, const size_t length) {
    if (span.size() < length) {
        throw std::length_error("not enough bytes");
    }
    return span.data();
}

std::span<const std::byte> DecodeWithLengthPrefix(std::span<const std::byte>& span) {
    const std::byte* source = span.data();
    size_t offset = 0;
    size_t length = DecodeLengthPrefix(source, offset, span.size());
    assert(offset == 1 || offset == 4);
    assert(offset <= span.size());
    if (span.size() - offset < length) {
        throw std::length_error("not enough bytes");
    }
    std::span<const std::byte> result = span.subspan(offset, length);
    span = span.subspan(offset + length);
    return result;
}
}
