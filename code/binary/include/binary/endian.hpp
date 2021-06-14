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

#if defined(__linux__) && (__BYTE_ORDER == __LITTLE_ENDIAN || __BYTE_ORDER == __BIG_ENDIAN)
        static const bool is_little_endian__ = __BYTE_ORDER == __LITTLE_ENDIAN;

        static uint16_t swap16__(uint16_t x) { return __bswap_16(x); }

        static uint32_t swap32__(uint32_t x) { return __bswap_32(x); }

        static uint64_t swap64__(uint64_t x) { return __bswap_64(x); }
#elif defined(_WIN32)
        static const bool is_little_endian__ = true;

        static uint16_t swap16__(uint16_t x) { return _byteswap_ushort(x); }

        static uint32_t swap32__(uint32_t x) { return _byteswap_ulong(x); }

        static uint64_t swap64__(uint64_t x) { return _byteswap_uint64(x); }
#else
#error "platform not supported"
#endif

        template <size_t N, typename std::enable_if<N == 1 || N == 2 || N == 4 || N == 8>::type* = nullptr>
        static void swap__(void* target, const void* source)
        {
            if constexpr (N == 1)
                *reinterpret_cast<uint8_t*>(target) = *reinterpret_cast<const uint8_t*>(source);
            else if constexpr (N == 2)
                *reinterpret_cast<uint16_t*>(target) = swap16__(*reinterpret_cast<const uint16_t*>(source));
            else if constexpr (N == 4)
                *reinterpret_cast<uint32_t*>(target) = swap32__(*reinterpret_cast<const uint32_t*>(source));
            else if constexpr (N == 8)
                *reinterpret_cast<uint64_t*>(target) = swap64__(*reinterpret_cast<const uint64_t*>(source));
        }

        template <typename T, bool Is>
        static void save__(void* target, T item)
        {
            if constexpr (Is)
                *reinterpret_cast<T*>(target) = item;
            else
                swap__<sizeof(T)>(target, &item);
        }

        template <typename T, bool Is>
        static T load__(const void* source)
        {
            T result;
            if constexpr (Is)
                result = *reinterpret_cast<const T*>(source);
            else
                swap__<sizeof(T)>(&result, &source);
            return result;
        }

    public:
        template <typename T>
        static void encode_little_endian(void* target, T item)
        {
            save__<T, is_little_endian__>(target, item);
        }

        template <typename T>
        static T decode_little_endian(const void* source)
        {
            return  load__<T, is_little_endian__>(source);
        }

        template <typename T>
        static void encode_big_endian(void* target, T item)
        {
            save__<T, is_little_endian__ == false>(target, item);
        }

        template <typename T>
        static T decode_big_endian(const void* source)
        {
            return  load__<T, is_little_endian__ == false>(source);
        }
    };
}
