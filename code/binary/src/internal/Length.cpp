#include "binary/internal/Length.hpp"

#include <cassert>
#include <format>
#include <stdexcept>

#include "binary/internal/Endian.hpp"
#include "binary/internal/Exception.hpp"

namespace binary::internal {
size_t GetCapacity(size_t byteLength, size_t itemLength, std::type_index type) {
    assert(byteLength != 0);
    assert(itemLength != 0);
    if ((byteLength % itemLength) != 0) {
        throw std::length_error(std::format("not enough bytes or byte sequence invalid, byte length: {}, type: {}", byteLength, type.name()));
    }
    return byteLength / itemLength;
}

void EnsureMemoryAccess(void* memory) {
    if (memory == nullptr) {
        throw std::runtime_error("invalid memory access or out of memory");
    }
}

void EnsureLengthPrefixLength(const size_t number) {
    if (number > INT32_MAX) {
        throw std::invalid_argument("number > INT32_MAX");
    }
}

size_t EncodeLengthPrefixLength(const size_t number) {
    assert(number <= INT32_MAX);
    if (number <= INT8_MAX) {
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
        ::binary::internal::ThrowNotEnoughBytes();
    }
    const std::byte* source = buffer + offset;
    uint32_t header = static_cast<uint32_t>(DecodeBigEndian<uint8_t>(source));
    offset += 1;
    if ((header & 0x80U) == 0U) {
        return header;
    }
    assert(limits >= offset);
    if (limits < offset + 3U) {
        ::binary::internal::ThrowNotEnoughBytes();
    }
    uint32_t result = DecodeBigEndian<uint32_t>(source);
    offset += 3;
    return result & 0x7FFF'FFFU;
}
}
