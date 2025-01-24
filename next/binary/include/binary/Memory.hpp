#ifndef BINARY_MEMORY_HPP
#define BINARY_MEMORY_HPP

#include <cstddef>
#include <span>

namespace binary {
class Allocator;

void Encode(Allocator& allocator, size_t number);
void Encode(std::span<std::byte> span, size_t number, size_t& bytesWritten);
void EncodeWithLengthPrefix(Allocator& allocator, const std::span<const std::byte>& span);
std::span<const std::byte> DecodeWithLengthPrefix(std::span<const std::byte>& span);
}

namespace binary::internal {
class AllocatorUnsafeAccessor {
public:
    static std::byte* Assign(Allocator& allocator, size_t length);
    static size_t Anchor(Allocator& allocator);
    static void FinishAnchor(Allocator& allocator, size_t anchor);
};

const std::byte* EnsureLength(const std::span<const std::byte>& span, const size_t length);
void EnsureLengthPrefixLength(const size_t number);
size_t EncodeLengthPrefixLength(const size_t number);
size_t DecodeLengthPrefixLength(const std::byte header);
void EncodeLengthPrefix(std::byte* buffer, const size_t number, const size_t length);
size_t DecodeLengthPrefix(const std::byte* buffer, size_t& offset, const size_t limits);
}

#endif
