#ifndef BINARY_INTERNAL_ENDIAN_HPP
#define BINARY_INTERNAL_ENDIAN_HPP

#include <concepts>
#include <cstddef>
#include <cstdint>

#if defined(__linux__)
#include <endian.h>
#elif defined(_WIN32)
#include <stdlib.h>
#endif

namespace binary::internal {
template <size_t Size>
void __binary_swap__(void* target, const void* source);

template <typename T, bool Is>
    requires std::same_as<T, std::remove_cv_t<T>>
inline void __binary_save__(void* target, T item) {
    if constexpr (Is || sizeof(T) == 1) {
        *static_cast<T*>(target) = item;
    } else {
        __binary_swap__<sizeof(T)>(target, &item);
    }
}

template <typename T, bool Is>
    requires std::same_as<T, std::remove_cv_t<T>>
inline T __binary_load__(const void* source) {
    if constexpr (Is || sizeof(T) == 1) {
        return *static_cast<const T*>(source);
    } else {
        T result{};
        __binary_swap__<sizeof(T)>(&result, source);
        return result;
    }
}

#if defined(__linux__) && (__BYTE_ORDER == __LITTLE_ENDIAN || __BYTE_ORDER == __BIG_ENDIAN)
constexpr bool IsLittleEndian = __BYTE_ORDER == __LITTLE_ENDIAN;
#elif defined(_WIN32)
constexpr bool IsLittleEndian = true;
#else
#error "platform not supported"
#endif

template <typename T>
inline void EncodeLittleEndian(void* target, T item) {
    __binary_save__<T, IsLittleEndian>(target, item);
}

template <typename T>
inline T DecodeLittleEndian(const void* source) {
    return __binary_load__<T, IsLittleEndian>(source);
}

template <typename T>
inline void EncodeBigEndian(void* target, T item) {
    __binary_save__<T, IsLittleEndian == false>(target, item);
}

template <typename T>
inline T DecodeBigEndian(const void* source) {
    return __binary_load__<T, IsLittleEndian == false>(source);
}
}

#endif
