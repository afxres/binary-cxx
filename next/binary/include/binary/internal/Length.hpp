#ifndef BINARY_INTERNAL_LENGTH_HPP
#define BINARY_INTERNAL_LENGTH_HPP

#include <cstddef>

namespace binary::internal {
void EnsureMemoryAccess(void* memory);
void EnsureLengthPrefixLength(const size_t number);
size_t EncodeLengthPrefixLength(const size_t number);
void EncodeLengthPrefix(std::byte* buffer, const size_t number, const size_t length);
size_t DecodeLengthPrefix(const std::byte* buffer, size_t& offset, const size_t limits);
}

#endif
