#pragma once

#ifndef BINARY_ENDIAN_HPP
#define BINARY_ENDIAN_HPP

#include <bit>
#include <cstddef>
#include <cstdint>

#if defined(__linux__)
#include <endian.h>
#elif defined(_WIN32)
#include <stdlib.h>
#endif

namespace binary::internal {
#if defined(__linux__) && (__BYTE_ORDER == __LITTLE_ENDIAN || __BYTE_ORDER == __BIG_ENDIAN)
constexpr bool __binary_is_little_endian__ = __BYTE_ORDER == __LITTLE_ENDIAN;

uint16_t __binary_swap16__(uint16_t x) {
    return __bswap_16(x);
}

uint32_t __binary_swap32__(uint32_t x) {
    return __bswap_32(x);
}

uint64_t __binary_swap64__(uint64_t x) {
    return __bswap_64(x);
}
#elif defined(_WIN32)
constexpr bool __binary_is_little_endian__ = true;

uint16_t __binary_swap16__(uint16_t x) {
    return _byteswap_ushort(x);
}

uint32_t __binary_swap32__(uint32_t x) {
    return _byteswap_ulong(x);
}

uint64_t __binary_swap64__(uint64_t x) {
    return _byteswap_uint64(x);
}
#else
#error "platform not supported"
#endif

template <size_t N, typename std::enable_if<N == 1 || N == 2 || N == 4 || N == 8>::type* = nullptr>
void __binary_swap__(void* target, const void* source) {
    if constexpr (N == 1) {
        *reinterpret_cast<uint8_t*>(target) = *reinterpret_cast<const uint8_t*>(source);
    } else if constexpr (N == 2) {
        *reinterpret_cast<uint16_t*>(target) = __binary_swap16__(*reinterpret_cast<const uint16_t*>(source));
    } else if constexpr (N == 4) {
        *reinterpret_cast<uint32_t*>(target) = __binary_swap32__(*reinterpret_cast<const uint32_t*>(source));
    } else if constexpr (N == 8) {
        *reinterpret_cast<uint64_t*>(target) = __binary_swap64__(*reinterpret_cast<const uint64_t*>(source));
    } else {
        static_assert(false, "invalid type size");
    }
}

template <typename T, bool Is>
void __binary_save__(void* target, T item) {
    if constexpr (Is) {
        *reinterpret_cast<T*>(target) = item;
    } else {
        __binary_swap__<sizeof(T)>(target, &item);
    }
}

template <typename T, bool Is>
T __binary_load__(const void* source) {
    T result;
    if constexpr (Is) {
        result = *reinterpret_cast<const T*>(source);
    } else {
        __binary_swap__<sizeof(T)>(&result, &source);
    }
    return result;
}
}

namespace binary {
constexpr bool IsLittleEndian = internal::__binary_is_little_endian__;

template <typename T>
void EncodeLittleEndian(void* target, T item) {
    internal::__binary_save__<T, internal::__binary_is_little_endian__>(target, item);
}

template <typename T>
T DecodeLittleEndian(const void* source) {
    return internal::__binary_load__<T, internal::__binary_is_little_endian__>(source);
}

template <typename T>
void EncodeBigEndian(void* target, T item) {
    internal::__binary_save__<T, internal::__binary_is_little_endian__ == false>(target, item);
}

template <typename T>
T DecodeBigEndian(const void* source) {
    return internal::__binary_load__<T, internal::__binary_is_little_endian__ == false>(source);
}
}

#endif
