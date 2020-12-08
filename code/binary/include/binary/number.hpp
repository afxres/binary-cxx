#pragma once

#include "abstract_buffer.hpp"
#include "endian.hpp"

#include <cassert>

namespace mikodev::binary
{
    using number_t = uint32_t;

    using number_length_t = uint32_t;

    class number
    {
    private:
        number() = delete;

    public:
        static number_length_t encode_length(number_t number)
        {
            assert(number <= std::numeric_limits<int32_t>::max());
            if ((static_cast<uint32_t>(number) >> 7) == 0)
                return 1;
            else
                return 4;
        }

        static number_length_t decode_length(byte_t header)
        {
            if ((static_cast<uint32_t>(header) & 0x80U) == 0)
                return 1;
            else
                return 4;
        }
    };
}
