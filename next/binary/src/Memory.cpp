#include "binary/Memory.hpp"

#include <cassert>
#include <cstddef>
#include <cstring>
#include <span>
#include <stdexcept>

#include "binary/Allocator.hpp"
#include "binary/internal/AllocatorUnsafeAccessor.hpp"
#include "binary/internal/Length.hpp"

namespace binary {
void Encode(Allocator& allocator, size_t number) {
    internal::EnsureLengthPrefixLength(number);
    size_t prefixLength = internal::EncodeLengthPrefixLength(number);
    std::byte* source = internal::AllocatorUnsafeAccessor::Assign(allocator, prefixLength);
    internal::EncodeLengthPrefix(source, number, prefixLength);
}

void Encode(std::span<std::byte> span, size_t number, size_t& bytesWritten) {
    internal::EnsureLengthPrefixLength(number);
    size_t prefixLength = internal::EncodeLengthPrefixLength(number);
    if (span.size() < prefixLength) {
        throw std::length_error("not enough bytes to write");
    }
    internal::EncodeLengthPrefix(span.data(), number, prefixLength);
    bytesWritten = prefixLength;
}

void EncodeWithLengthPrefix(Allocator& allocator, const std::span<const std::byte>& span) {
    size_t number = span.size();
    internal::EnsureLengthPrefixLength(number);
    size_t prefixLength = internal::EncodeLengthPrefixLength(number);
    std::byte* source = internal::AllocatorUnsafeAccessor::Assign(allocator, number + prefixLength);
    internal::EncodeLengthPrefix(source, number, prefixLength);
    memcpy(source + prefixLength, span.data(), number);
}

std::span<const std::byte> DecodeWithLengthPrefix(std::span<const std::byte>& span) {
    const std::byte* source = span.data();
    size_t offset = 0;
    size_t length = internal::DecodeLengthPrefix(source, offset, span.size());
    assert(offset == 1 || offset == 4);
    assert(offset <= span.size());
    if (span.size() < offset + length) {
        throw std::length_error("not enough bytes");
    }
    std::span<const std::byte> result = span.subspan(offset, length);
    span = span.subspan(offset + length);
    return result;
}
}
