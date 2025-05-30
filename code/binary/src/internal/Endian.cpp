#include "binary/internal/Endian.hpp"

#include <cstdint>

namespace binary::internal {
#if defined(__linux__)
uint16_t __swap16__(uint16_t x) {
    return __bswap_16(x);
}

uint32_t __swap32__(uint32_t x) {
    return __bswap_32(x);
}

uint64_t __swap64__(uint64_t x) {
    return __bswap_64(x);
}
#elif defined(_WIN32)
uint16_t __swap16__(uint16_t x) {
    return _byteswap_ushort(x);
}

uint32_t __swap32__(uint32_t x) {
    return _byteswap_ulong(x);
}

uint64_t __swap64__(uint64_t x) {
    return _byteswap_uint64(x);
}
#endif

template <>
void Swap<2>(void* target, const void* source) {
    *static_cast<uint16_t*>(target) = __swap16__(*static_cast<const uint16_t*>(source));
}

template <>
void Swap<4>(void* target, const void* source) {
    *static_cast<uint32_t*>(target) = __swap32__(*static_cast<const uint32_t*>(source));
}

template <>
void Swap<8>(void* target, const void* source) {
    *static_cast<uint64_t*>(target) = __swap64__(*static_cast<const uint64_t*>(source));
}
}
