#pragma once

#include <endian.h>

namespace mikodev::binary
{
    template <typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value && (sizeof(T) == 1 || sizeof(T) == 2 || sizeof(T) == 4 || sizeof(T) == 8), T>::type>
    class endian
    {
    private:
        endian() = delete;

    public:
        static T ensure_little_endian(T item)
        {
            if constexpr (sizeof(T) == 1)
                return item;
            else if constexpr (sizeof(T) == 2)
                return reinterpret_cast<T>(htole16(reinterpret_cast<uint16_t>(item)));
            else if constexpr (sizeof(T) == 4)
                return reinterpret_cast<T>(htole32(reinterpret_cast<uint32_t>(item)));
            else if constexpr (sizeof(T) == 8)
                return reinterpret_cast<T>(htole64(reinterpret_cast<uint64_t>(item)));
        }

        static T ensure_big_endian(T item)
        {
            if constexpr (sizeof(T) == 1)
                return item;
            else if constexpr (sizeof(T) == 2)
                return reinterpret_cast<T>(htobe16(reinterpret_cast<uint16_t>(item)));
            else if constexpr (sizeof(T) == 4)
                return reinterpret_cast<T>(htobe32(reinterpret_cast<uint32_t>(item)));
            else if constexpr (sizeof(T) == 8)
                return reinterpret_cast<T>(htobe64(reinterpret_cast<uint64_t>(item)));
        }
    };
}
