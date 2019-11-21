#pragma once

#include "allocator_base.hpp"
#include "span_view_base.hpp"
#include "exceptions/throw_helper.hpp"

#include <cassert>
#include <memory>

namespace mikodev::binary
{
    using number_t = uint32_t;

    using number_length_t = size_t;

    class primitive_helper
    {
    private:
        primitive_helper() = delete;

    public:
        static number_length_t encode_number_length(number_t number)
        {
            if (number < 0x40)
                return 1;
            if (number < 0x4000)
                return 2;
            else
                return 4;
        }

        static number_length_t decode_number_length(byte_t header)
        {
            number_length_t result = static_cast<number_length_t>(header) >> 6;
            if (result > 1)
                result = 3;
            return result + 1;
        }

        static void encode_number_fixed4(byte_t* data, number_t number)
        {
            assert(number >= 0 && number <= INT32_MAX);

            data[0] = static_cast<byte_t>((number >> 24) | 0x80);
            data[1] = static_cast<byte_t>(number >> 16);
            data[2] = static_cast<byte_t>(number >> 8);
            data[3] = static_cast<byte_t>(number);
        }

        static void encode_number(byte_t* data, number_length_t length, number_t number)
        {
            assert(number >= 0 && number <= INT32_MAX);
            assert(length == 1 || length == 2 || length == 4);

            if (length == 1)
            {
                data[0] = static_cast<byte_t>(number);
            }
            else if (length == 2)
            {
                data[0] = static_cast<byte_t>((number >> 8) | 0x40);
                data[1] = static_cast<byte_t>(number);
            }
            else
            {
                encode_number_fixed4(data, number);
            }
        }

        static number_t decode_number(const byte_t* data, number_length_t length)
        {
            assert(length == 1 || length == 2 || length == 4);
            if (length == 1)
                return static_cast<number_t>(data[0]) & 0x3F;
            if (length == 2)
                return ((static_cast<number_t>(data[0]) & 0x3F) << 8) | static_cast<number_t>(data[1]);
            else
                return ((static_cast<number_t>(data[0]) & 0x7F) << 24) | (static_cast<number_t>(data[1]) << 16) | (static_cast<number_t>(data[2]) << 8) | static_cast<number_t>(data[3]);
        }

        static void encode_number(allocator_base& allocator, size_t number)
        {
            if (number > INT32_MAX)
                exceptions::throw_helper::throw_argument_exception();
            number_length_t length = encode_number_length(static_cast<number_t>(number));
            byte_t* location = allocator._allocate(length);
            encode_number(location, length, static_cast<number_t>(number));
        }

        static size_t decode_number(span_view_base& span)
        {
            if (span.size() == 0)
                exceptions::throw_helper::throw_argument_exception();
            const byte_t* data = span.data();
            number_length_t length = decode_number_length(data[0]);
            // check bounds via slice method
            span.slice_this(length);
            number_t number = decode_number(data, length);
            return static_cast<size_t>(number);
        }

        static std::unique_ptr<span_view_base> decode_buffer_with_length_prefix(span_view_base& span)
        {
            number_t length;
            number_length_t number_length;
            size_t limits = span.size();
            const byte_t* location = span.data();
            if (limits == 0 || limits < (number_length = decode_number_length(*location)) || (limits - number_length) < (length = decode_number(location, number_length)))
                exceptions::throw_helper::throw_not_enough_bytes();

            std::unique_ptr<span_view_base> view = span.slice(number_length, length);
            span.slice_this(number_length + length);
            return view;
        }
    };
}
