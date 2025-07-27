#ifndef BINARY_INTERNAL_ENDIAN_HPP
#define BINARY_INTERNAL_ENDIAN_HPP

#include <bit>
#include <concepts>
#include <cstddef>
#include <cstdint>

namespace binary::internal {
#if defined(__GNUC__)
#define __swap16__ __builtin_bswap16
#define __swap32__ __builtin_bswap32
#define __swap64__ __builtin_bswap64
#elif defined(_WIN32)
#define __swap16__ _byteswap_ushort
#define __swap32__ _byteswap_ulong
#define __swap64__ _byteswap_uint64
#endif

template <typename Item>
    requires std::same_as<Item, std::remove_cv_t<Item>>
void SaveUnaligned(void* target, Item item) {
    *static_cast<Item*>(target) = item;
}

template <typename Item>
    requires std::same_as<Item, std::remove_cv_t<Item>>
Item LoadUnaligned(const void* source) {
    return *static_cast<const Item*>(source);
}

#define SaveSwapTest(Size)                                                                   \
    if constexpr (sizeof(Item) == sizeof(uint##Size##_t)) {                                  \
        return SaveUnaligned(target, __swap##Size##__(std::bit_cast<uint##Size##_t>(item))); \
    }

#define LoadSwapTest(Size)                                                                   \
    if constexpr (sizeof(Item) == sizeof(uint##Size##_t)) {                                  \
        return std::bit_cast<Item>(__swap##Size##__(LoadUnaligned<uint##Size##_t>(source))); \
    }

template <typename Item, std::endian E>
    requires std::same_as<Item, std::remove_cv_t<Item>>
void Save(void* target, Item item) {
    if constexpr (std::endian::native == E || sizeof(Item) == 1) {
        SaveUnaligned(target, item);
    } else {
        SaveSwapTest(16);
        SaveSwapTest(32);
        SaveSwapTest(64);
        static_assert("type not supported");
    }
}

template <typename Item, std::endian E>
    requires std::same_as<Item, std::remove_cv_t<Item>>
Item Load(const void* source) {
    if constexpr (std::endian::native == E || sizeof(Item) == 1) {
        return LoadUnaligned<Item>(source);
    } else {
        LoadSwapTest(16);
        LoadSwapTest(32);
        LoadSwapTest(64);
        static_assert("type not supported");
    }
}

template <typename Item>
void EncodeLittleEndian(void* target, Item item) {
    Save<Item, std::endian::little>(target, item);
}

template <typename Item>
Item DecodeLittleEndian(const void* source) {
    return Load<Item, std::endian::little>(source);
}

template <typename Item>
void EncodeBigEndian(void* target, Item item) {
    Save<Item, std::endian::big>(target, item);
}

template <typename Item>
Item DecodeBigEndian(const void* source) {
    return Load<Item, std::endian::big>(source);
}
}

#endif
