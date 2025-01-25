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

#endif
