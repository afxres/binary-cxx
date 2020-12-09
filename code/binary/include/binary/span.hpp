#pragma once

#include "abstract_buffer.hpp"

namespace mikodev::binary
{
    class span
    {
    private:
        abstract_buffer_ptr buffer_;

        byte_ptr memory_;

        size_t length_;

        span(abstract_buffer_ptr buffer, byte_ptr memory, size_t length) : buffer_(buffer), memory_(memory), length_(length) {}

    public:
        span(abstract_buffer_ptr buffer) : span(buffer, buffer == nullptr ? nullptr : buffer->buffer(), buffer == nullptr ? 0 : buffer->length()) {}

        span(span&&) = default;

        span(const span&) = default;

        virtual ~span() = default;

        byte_ptr buffer() { return memory_; }

        size_t length() { return length_; }

        span slice(size_t offset)
        {
            if (length_ < offset)
                exceptions::throw_helper::throw_argument_exception();
            return span(buffer_, memory_ + offset, length_ - offset);
        }

        span slice(size_t offset, size_t length)
        {
            if (length_ < offset || length_ - offset < length)
                exceptions::throw_helper::throw_argument_exception();
            return span(buffer_, memory_ + offset, length);
        }
    };
}
