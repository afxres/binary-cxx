#pragma once

#include "define.hpp"
#include "endian.hpp"
#include "exceptions/throw_helper.hpp"

#include <cassert>

namespace mikodev::binary
{
    using number_t = uint32_t;

    class number
    {
    private:
        number() = delete;

        friend class allocator;

        friend class converter;

        template <typename T>
        static void encode(byte_ptr buffer, T data)
        {
            *reinterpret_cast<T*>(buffer) = endian::ensure_big_endian<T>(data);
        }

        static void encode(byte_ptr buffer, number_t number, length_t length)
        {
            assert(length == 1 || length == 4);
            assert(length >= encode_length(number));
            assert(static_cast<length_t>(number) <= length_max);
            if (length == 1)
                encode<uint8_t>(buffer, static_cast<uint8_t>(number));
            else
                encode<uint32_t>(buffer, static_cast<uint32_t>(number) | 0x8000'0000);
        }

        template <typename T>
        static T decode(const_byte_ptr buffer)
        {
            return endian::ensure_big_endian<T>(*reinterpret_cast<const T*>(buffer));
        }

        static number_t decode(const_byte_ptr buffer, length_t& offset, length_t limits)
        {
            assert(limits >= offset);
            if (limits == offset)
                exceptions::throw_helper::throw_not_enough_bytes();
            const_byte_ptr source = buffer + offset;
            uint32_t header = static_cast<uint32_t>(decode<uint8_t>(source));
            offset += 1;
            if ((header & 0x80U) == 0)
                return static_cast<number_t>(header);
            assert(limits >= offset);
            if (limits - offset < 3U)
                exceptions::throw_helper::throw_not_enough_bytes();
            uint32_t result = decode<uint32_t>(source);
            offset += 3;
            return static_cast<number_t>(result & 0x7FFF'FFFU);
        }

        static length_t decode_ensure_buffer(const_byte_ptr buffer, length_t& offset, length_t limits)
        {
            assert(limits >= offset);
            length_t length = static_cast<length_t>(decode(buffer, offset, limits));
            assert(limits >= offset);
            if (limits - offset < length)
                exceptions::throw_helper::throw_not_enough_bytes();
            return length;
        }

    public:
        static length_t encode_length(number_t number)
        {
            assert(static_cast<length_t>(number) <= length_max);
            if ((static_cast<uint32_t>(number) >> 7) == 0)
                return 1;
            else
                return 4;
        }

        static length_t decode_length(byte_t header)
        {
            if ((static_cast<uint32_t>(header) & 0x80U) == 0)
                return 1;
            else
                return 4;
        }
    };
}
