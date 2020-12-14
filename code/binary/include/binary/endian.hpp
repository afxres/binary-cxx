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
        static inline R __cast(T item) { return *reinterpret_cast<R*>(&item); }

    public:
        template <typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value && (sizeof(T) == 1 || sizeof(T) == 2 || sizeof(T) == 4 || sizeof(T) == 8), T>::type>
        static T ensure_little_endian(T item)
        {
            if constexpr (sizeof(T) == 1)
                return item;
#if defined(__linux__)
            else if constexpr (sizeof(T) == 2)
                return __cast<uint16_t, T>(htole16((__cast<T, uint16_t>(item))));
            else if constexpr (sizeof(T) == 4)
                return __cast<uint32_t, T>(htole32((__cast<T, uint32_t>(item))));
            else if constexpr (sizeof(T) == 8)
                return __cast<uint64_t, T>(htole64((__cast<T, uint64_t>(item))));
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
                return __cast<uint16_t, T>(_byteswap_ushort(__cast<T, uint16_t>(item)));
            else if constexpr (sizeof(T) == 4)
                return __cast<uint32_t, T>(_byteswap_ulong(__cast<T, uint32_t>(item)));
            else if constexpr (sizeof(T) == 8)
                return __cast<uint64_t, T>(_byteswap_uint64(__cast<T, uint64_t>(item)));
#endif
        }
    };
}
