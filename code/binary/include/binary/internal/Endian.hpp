#ifndef BINARY_INTERNAL_ENDIAN_HPP
#define BINARY_INTERNAL_ENDIAN_HPP

#include <bit>
#include <concepts>
#include <cstddef>
#include <cstdint>
#include <cstring>

namespace binary::internal {
#if defined(__GNUC__)
#define BINARY_INTERNAL_SWAP_16 __builtin_bswap16
#define BINARY_INTERNAL_SWAP_32 __builtin_bswap32
#define BINARY_INTERNAL_SWAP_64 __builtin_bswap64
#elif defined(_WIN32)
#define BINARY_INTERNAL_SWAP_16 _byteswap_ushort
#define BINARY_INTERNAL_SWAP_32 _byteswap_ulong
#define BINARY_INTERNAL_SWAP_64 _byteswap_uint64
#endif

template <typename Item>
    requires std::same_as<Item, std::remove_cv_t<Item>>
void SaveUnaligned(void* target, Item item) {
    memcpy(target, &item, sizeof(Item));
}

template <typename Item>
    requires std::same_as<Item, std::remove_cv_t<Item>>
Item LoadUnaligned(const void* source) {
    Item item;
    memcpy(&item, source, sizeof(Item));
    return item;
}

// Byte reversal is its own inverse, so both directions share this routine.
inline void Swap128(void* target, const void* source) {
    const auto head = LoadUnaligned<std::uint64_t>(source);
    const auto tail = LoadUnaligned<std::uint64_t>(static_cast<const std::byte*>(source) + sizeof(head));
    SaveUnaligned(target, BINARY_INTERNAL_SWAP_64(tail));
    SaveUnaligned(static_cast<std::byte*>(target) + sizeof(tail), BINARY_INTERNAL_SWAP_64(head));
}

#define BINARY_INTERNAL_SWAP_SAVE_TEST(Size)                                                            \
    if constexpr (sizeof(Item) == sizeof(uint##Size##_t)) {                                             \
        return SaveUnaligned(target, BINARY_INTERNAL_SWAP_##Size(std::bit_cast<uint##Size##_t>(item))); \
    }

#define BINARY_INTERNAL_SWAP_LOAD_TEST(Size)                                                            \
    if constexpr (sizeof(Item) == sizeof(uint##Size##_t)) {                                             \
        return std::bit_cast<Item>(BINARY_INTERNAL_SWAP_##Size(LoadUnaligned<uint##Size##_t>(source))); \
    }

template <typename Item, std::endian E>
    requires std::same_as<Item, std::remove_cv_t<Item>>
void Save(void* target, Item item) {
    if constexpr (std::endian::native == E || sizeof(Item) == 1) {
        SaveUnaligned(target, item);
    } else if constexpr (sizeof(Item) == 16) {
        Swap128(target, &item);
    } else {
        BINARY_INTERNAL_SWAP_SAVE_TEST(16);
        BINARY_INTERNAL_SWAP_SAVE_TEST(32);
        BINARY_INTERNAL_SWAP_SAVE_TEST(64);
        static_assert(sizeof(Item) == 2 || sizeof(Item) == 4 || sizeof(Item) == 8, "type not supported");
    }
}

template <typename Item, std::endian E>
    requires std::same_as<Item, std::remove_cv_t<Item>>
Item Load(const void* source) {
    if constexpr (std::endian::native == E || sizeof(Item) == 1) {
        return LoadUnaligned<Item>(source);
    } else if constexpr (sizeof(Item) == 16) {
        Item item{};
        Swap128(&item, source);
        return item;
    } else {
        BINARY_INTERNAL_SWAP_LOAD_TEST(16);
        BINARY_INTERNAL_SWAP_LOAD_TEST(32);
        BINARY_INTERNAL_SWAP_LOAD_TEST(64);
        static_assert(sizeof(Item) == 2 || sizeof(Item) == 4 || sizeof(Item) == 8, "type not supported");
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
