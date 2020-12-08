#pragma once

#include "abstract_buffer.hpp"

namespace mikodev::binary
{
    class span
    {
    private:
        abstract_buffer_ptr buffer_;

        size_t offset_;

        size_t length_;

        span(abstract_buffer_ptr buffer, size_t offset, size_t length) : buffer_(buffer), offset_(offset), length_(length) {}

    public:
        span(abstract_buffer_ptr buffer) : span(buffer, 0, buffer == nullptr ? 0 : buffer->length()) {}

        span(span&& _) = default;

        span(const span& _) = default;

        virtual ~span() = default;

        byte_ptr buffer() { return buffer_->buffer() + offset_; }

        size_t length() { return length_; }

        span slice(size_t offset)
        {
            if (length_ < offset)
                exceptions::throw_helper::throw_argument_exception();
            return span(buffer_, offset, length_ - offset);
        }

        span slice(size_t offset, size_t length)
        {
            if (length_ < offset || length_ - offset < length)
                exceptions::throw_helper::throw_argument_exception();
            return span(buffer_, offset, length);
        }
    };
}
