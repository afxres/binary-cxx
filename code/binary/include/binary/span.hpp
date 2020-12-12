#pragma once

#include "abstract_buffer.hpp"
#include "exceptions/throw_helper.hpp"

namespace mikodev::binary
{
    class span final
    {
        friend class converter;

    private:
        abstract_buffer_ptr shared_;

        const_byte_ptr buffer_;

        size_t length_;

        span(abstract_buffer_ptr shared, const_byte_ptr buffer, size_t length) : shared_(shared), buffer_(buffer), length_(length) {}

        span __slice_unchecked__(size_t offset, size_t length)
        {
            assert(offset <= length_);
            assert(length <= length_);
            assert(offset + length <= length_);
            return span(shared_, buffer_ + offset, length_ - offset);
        }

        static void __slice_in_place_unchecked__(span& span, size_t offset)
        {
            assert(offset <= span.length_);
            span.buffer_ += offset;
            span.length_ -= offset;
        }

    public:
        span() : span(nullptr, nullptr, 0) {}

        span(const_byte_ptr buffer, size_t length) : span(nullptr, buffer, length) {}

        span(abstract_buffer_ptr shared) : span(shared, shared == nullptr ? nullptr : shared->buffer(), shared == nullptr ? 0 : shared->length()) {}

        const_byte_ptr buffer() { return buffer_; }

        size_t length() { return length_; }

        span slice(size_t offset)
        {
            if (length_ < offset)
                exceptions::throw_helper::throw_argument_exception();
            return span(shared_, buffer_ + offset, length_ - offset);
        }

        span slice(size_t offset, size_t length)
        {
            if (length_ < offset || length_ - offset < length)
                exceptions::throw_helper::throw_argument_exception();
            return span(shared_, buffer_ + offset, length);
        }
    };
}
