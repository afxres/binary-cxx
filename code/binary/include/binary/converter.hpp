#pragma once

#include "allocator.hpp"
#include "number.hpp"
#include "span.hpp"

namespace mikodev::binary
{
    class converter
    {
    private:
        converter() = delete;

    public:
        static void encode(allocator& allocator, number_t number)
        {
            if (static_cast<size_t>(number) > number::max_supported_size)
                exceptions::throw_helper::throw_argument_out_of_range_exception();
            length_t number_length = number::encode_length(number);
            number::encode(allocator::assign__(allocator, static_cast<size_t>(number_length)), number, number_length);
        }

        static void encode_with_length_prefix(allocator& allocator, const_byte_ptr buffer, size_t length)
        {
            if (length > number::max_supported_size)
                exceptions::throw_helper::throw_argument_out_of_range_exception();
            length_t number_length = number::encode_length(static_cast<number_t>(length));
            byte_ptr target = allocator::assign__(allocator, length + static_cast<size_t>(number_length));
            number::encode(target, static_cast<number_t>(length), number_length);
            if (length == 0)
                return;
            std::memcpy(target + static_cast<size_t>(number_length), buffer, length);
        }

        static number_t decode(span& span)
        {
            size_t offset = 0;
            number_t length = number::decode(span.buffer(), offset, span.length());
            span::__slice_in_place_unchecked__(span, offset);
            return length;
        }

        static span decode_with_length_prefix(span& span)
        {
            size_t offset = 0;
            number_t length = number::decode_ensure_buffer(span.buffer(), offset, span.length());
            size_t cursor = offset + static_cast<size_t>(length);
            binary::span result = span.__slice_unchecked__(offset, length);
            span::__slice_in_place_unchecked__(span, cursor);
            return result;
        }
    };
}
