#pragma once

#ifndef BINARY_MEMORY_HPP
#define BINARY_MEMORY_HPP

#include <cstddef>
#include <span>

namespace binary {
size_t EncodeLengthPrefixLength(const size_t number);
size_t DecodeLengthPrefixLength(const std::byte header);
void EncodeLengthPrefix(std::byte* buffer, const size_t number, const size_t length);
size_t DecodeLengthPrefix(const std::byte* buffer, size_t& offset, const size_t limits);
size_t EnsureLength(const size_t length);
const std::byte* EnsureLength(const std::span<const std::byte>& span, const size_t length);
std::span<const std::byte> DecodeWithLengthPrefix(std::span<const std::byte>& span);
}

#endif
