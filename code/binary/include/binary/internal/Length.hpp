#ifndef BINARY_INTERNAL_LENGTH_HPP
#define BINARY_INTERNAL_LENGTH_HPP

#include <cstddef>
#include <typeindex>

namespace binary::internal {
size_t GetCapacity(size_t byteLength, size_t itemLength, std::type_index type);
void EnsureMemoryAccess(void* memory);
void EnsureLengthPrefixLength(size_t number);
size_t EncodeLengthPrefixLength(size_t number);
void EncodeLengthPrefix(std::byte* buffer, size_t number, size_t length);
size_t DecodeLengthPrefix(const std::byte* buffer, size_t& offset, size_t limits);
}

#endif
