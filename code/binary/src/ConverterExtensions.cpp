#include "binary/ConverterExtensions.hpp"

#include <cassert>
#include <cstddef>
#include <cstring>
#include <span>

#include "binary/Allocator.hpp"
#include "binary/internal/AllocatorUnsafeAccessor.hpp"
#include "binary/internal/Exception.hpp"
#include "binary/internal/Length.hpp"

namespace binary {
void Encode(Allocator& allocator, size_t number) {
    ::binary::internal::EnsureLengthPrefixLength(number);
    size_t prefixLength = ::binary::internal::EncodeLengthPrefixLength(number);
    std::byte* source = ::binary::internal::AllocatorUnsafeAccessor::Assign(allocator, prefixLength);
    ::binary::internal::EncodeLengthPrefix(source, number, prefixLength);
}

void Encode(std::span<std::byte> span, size_t number, size_t& bytesWritten) {
    ::binary::internal::EnsureLengthPrefixLength(number);
    size_t prefixLength = ::binary::internal::EncodeLengthPrefixLength(number);
    if (span.size() < prefixLength) {
        ::binary::internal::ThrowNotEnoughBytesToWrite();
    }
    ::binary::internal::EncodeLengthPrefix(span.data(), number, prefixLength);
    bytesWritten = prefixLength;
}

void EncodeWithLengthPrefix(Allocator& allocator, const std::span<const std::byte>& span) {
    size_t number = span.size();
    ::binary::internal::EnsureLengthPrefixLength(number);
    size_t prefixLength = ::binary::internal::EncodeLengthPrefixLength(number);
    std::byte* source = ::binary::internal::AllocatorUnsafeAccessor::Assign(allocator, number + prefixLength);
    ::binary::internal::EncodeLengthPrefix(source, number, prefixLength);
    memcpy(source + prefixLength, span.data(), number);
}

size_t Decode(std::span<const std::byte>& span) {
    const std::byte* source = span.data();
    size_t offset = 0;
    size_t length = ::binary::internal::DecodeLengthPrefix(source, offset, span.size());
    assert(offset == 1 || offset == 4);
    assert(offset <= span.size());
    span = span.subspan(offset);
    return length;
}

size_t Decode(const std::span<const std::byte>& span, size_t& bytesRead) {
    const std::byte* source = span.data();
    size_t offset = 0;
    size_t length = ::binary::internal::DecodeLengthPrefix(source, offset, span.size());
    assert(offset == 1 || offset == 4);
    assert(offset <= span.size());
    bytesRead = offset;
    return length;
}

std::span<const std::byte> DecodeWithLengthPrefix(std::span<const std::byte>& span) {
    const std::byte* source = span.data();
    size_t offset = 0;
    size_t length = ::binary::internal::DecodeLengthPrefix(source, offset, span.size());
    assert(offset == 1 || offset == 4);
    assert(offset <= span.size());
    if (span.size() < offset + length) {
        ::binary::internal::ThrowNotEnoughBytes();
    }
    std::span<const std::byte> result = span.subspan(offset, length);
    span = span.subspan(offset + length);
    return result;
}
}
