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
            if (static_cast<length_t>(number) > length_max)
                exceptions::throw_helper::throw_argument_out_of_range_exception();
            length_t number_length = number::encode_length(number);
            number::encode(allocator::assign__(allocator, static_cast<length_t>(number_length)), number, number_length);
        }

        static void encode_with_length_prefix(allocator& allocator, const_byte_ptr buffer, length_t length)
        {
            if (length > length_max)
                exceptions::throw_helper::throw_argument_out_of_range_exception();
            length_t number_length = number::encode_length(static_cast<number_t>(length));
            byte_ptr target = allocator::assign__(allocator, length + number_length);
            number::encode(target, static_cast<number_t>(length), number_length);
            if (length == 0)
                return;
            std::memcpy(target + number_length, buffer, length);
        }

        static number_t decode(span& span)
        {
            const_byte_ptr buffer = span.buffer_;
            length_t length = span.length_;
            length_t offset = 0;
            number_t number = number::decode(buffer, offset, length);
            assert(offset <= span.length_);
            span.buffer_ = buffer + offset;
            span.length_ = length - offset;
            return number;
        }

        static span decode_with_length_prefix(span& span)
        {
            const_byte_ptr buffer = span.buffer_;
            length_t length = span.length_;
            length_t offset = 0;
            length_t number = number::decode_ensure_buffer(buffer, offset, length);
            length_t cursor = offset + number;
            assert(cursor <= span.length_);
            span.buffer_ = buffer + cursor;
            span.length_ = length - cursor;
            return binary::span(span.shared_, buffer + offset, number);
        }
    };
}
