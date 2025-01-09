#pragma once

#ifndef BINARY_MEMORY_HPP
#define BINARY_MEMORY_HPP

#include <cstddef>
#include <cstdint>
#include <span>

namespace binary {
int32_t EncodeLengthPrefixLength(const int32_t number);
int32_t DecodeLengthPrefixLength(const std::byte header);
void EncodeLengthPrefix(std::byte* buffer, const int32_t number, const int32_t length);
size_t DecodeLengthPrefix(const std::byte* buffer, size_t& offset, const size_t limits);
int32_t EnsureLength(const size_t length);
const std::byte* EnsureLength(const std::span<const std::byte>& span, const int32_t length);
std::span<const std::byte> DecodeWithLengthPrefix(std::span<const std::byte>& span);
}

#endif
