#pragma once

#if defined(__linux__)
#include <endian.h>
#endif

#if defined(_WIN32)
#include <stdlib.h>
#endif

namespace mikodev::binary
{
    class endian
    {
    private:
        endian() = delete;

        template <typename T, typename R>
        static inline R __cast__(T item) { return *reinterpret_cast<R*>(&item); }

#if defined(__linux__) && (__BYTE_ORDER == __LITTLE_ENDIAN || __BYTE_ORDER == __BIG_ENDIAN)
        static const bool __is_little_endian = __BYTE_ORDER == __LITTLE_ENDIAN;

        static uint16_t __swap16(uint16_t x) { return __bswap_16(x); }

        static uint32_t __swap32(uint32_t x) { return __bswap_32(x); }

        static uint64_t __swap64(uint64_t x) { return __bswap_64(x); }
#elif defined(_WIN32)
        static const bool __is_little_endian = true;

        static uint16_t __swap16(uint16_t x) { return _byteswap_ushort(x); }

        static uint32_t __swap32(uint32_t x) { return _byteswap_ulong(x); }

        static uint64_t __swap64(uint64_t x) { return _byteswap_uint64(x); }
#else
#error "platform not supported"
#endif

    public:
        template <typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value && (sizeof(T) == 1 || sizeof(T) == 2 || sizeof(T) == 4 || sizeof(T) == 8), T>::type>
        static T swap(T item)
        {
            if constexpr (sizeof(T) == 1)
                return item;
            else if constexpr (sizeof(T) == 2)
                return __cast__<uint16_t, T>(__swap16(__cast__<T, uint16_t>(item)));
            else if constexpr (sizeof(T) == 4)
                return __cast__<uint32_t, T>(__swap32(__cast__<T, uint32_t>(item)));
            else if constexpr (sizeof(T) == 8)
                return __cast__<uint64_t, T>(__swap64(__cast__<T, uint64_t>(item)));
        }

        template <size_t N, typename std::enable_if<N == 1 || N == 2 || N == 4 || N == 8>::type* = nullptr>
        static void swap(void* target, const void* source)
        {
            if constexpr (N == 1)
                *reinterpret_cast<uint8_t*>(target) = *reinterpret_cast<const uint8_t*>(source);
            else if constexpr (N == 2)
                *reinterpret_cast<uint16_t*>(target) = __swap16(*reinterpret_cast<const uint16_t*>(source));
            else if constexpr (N == 4)
                *reinterpret_cast<uint32_t*>(target) = __swap32(*reinterpret_cast<const uint32_t*>(source));
            else if constexpr (N == 8)
                *reinterpret_cast<uint64_t*>(target) = __swap64(*reinterpret_cast<const uint64_t*>(source));
        }

        template <typename T>
        static void encode_little_endian(void* target, T item)
        {
            if constexpr (__is_little_endian)
                *reinterpret_cast<T*>(target) = item;
            else
                swap<sizeof(T)>(target, &item);
        }

        template <typename T>
        static T decode_little_endian(const void* source)
        {
            T result;
            if constexpr (__is_little_endian)
                result = *reinterpret_cast<const T*>(source);
            else
                swap<sizeof(T)>(&result, &source);
            return result;
        }

        template <typename T>
        static void encode_big_endian(void* target, T item)
        {
            if constexpr (!__is_little_endian)
                *reinterpret_cast<T*>(target) = item;
            else
                swap<sizeof(T)>(target, &item);
        }

        template <typename T>
        static T decode_big_endian(const void* source)
        {
            T result;
            if constexpr (!__is_little_endian)
                result = *reinterpret_cast<T*>(source);
            else
                swap<sizeof(T)>(&result, &source);
            return result;
        }

        template <typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value && (sizeof(T) == 1 || sizeof(T) == 2 || sizeof(T) == 4 || sizeof(T) == 8), T>::type>
        static T ensure_little_endian(T item)
        {
            if constexpr (sizeof(T) == 1)
                return item;
#if defined(__linux__)
            else if constexpr (sizeof(T) == 2)
                return __cast__<uint16_t, T>(htole16((__cast__<T, uint16_t>(item))));
            else if constexpr (sizeof(T) == 4)
                return __cast__<uint32_t, T>(htole32((__cast__<T, uint32_t>(item))));
            else if constexpr (sizeof(T) == 8)
                return __cast__<uint64_t, T>(htole64((__cast__<T, uint64_t>(item))));
#elif defined(_WIN32)
            return item;
#endif
        }

        template <typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value && (sizeof(T) == 1 || sizeof(T) == 2 || sizeof(T) == 4 || sizeof(T) == 8), T>::type>
        static T ensure_big_endian(T item)
        {
            if constexpr (sizeof(T) == 1)
                return item;
#if defined(__linux__)
            else if constexpr (sizeof(T) == 2)
                return reinterpret_cast<T>(htobe16(reinterpret_cast<uint16_t>(item)));
            else if constexpr (sizeof(T) == 4)
                return reinterpret_cast<T>(htobe32(reinterpret_cast<uint32_t>(item)));
            else if constexpr (sizeof(T) == 8)
                return reinterpret_cast<T>(htobe64(reinterpret_cast<uint64_t>(item)));
#elif defined(_WIN32)
            else if constexpr (sizeof(T) == 2)
                return __cast__<uint16_t, T>(_byteswap_ushort(__cast__<T, uint16_t>(item)));
            else if constexpr (sizeof(T) == 4)
                return __cast__<uint32_t, T>(_byteswap_ulong(__cast__<T, uint32_t>(item)));
            else if constexpr (sizeof(T) == 8)
                return __cast__<uint64_t, T>(_byteswap_uint64(__cast__<T, uint64_t>(item)));
#endif
        }
    };
}
