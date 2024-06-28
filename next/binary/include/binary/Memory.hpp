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
int32_t DecodeLengthPrefix(const std::byte* buffer, int32_t& offset, const int32_t limits);
int32_t EnsureLength(size_t length);
std::span<std::byte> DecodeWithLengthPrefix(std::span<std::byte>& span);
}

#endif
