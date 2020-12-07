#pragma once

#include "abstract_buffer.hpp"

#include <cassert>
#include <cstring>

namespace mikodev::binary
{
    class allocator
    {
    private:
        abstract_buffer_ptr buffer_;

        size_t offset_;

        size_t bounds_;

        size_t limits_;

        static void resize(allocator& allocator, size_t length)
        {
            assert(length > 0);
            size_t bounds = allocator.bounds_;
            uintmax_t amount = bounds + length;
            if (amount >= allocator.limits_)
                exceptions::throw_helper::throw_capacity_limited();

            const size_t initial_capacity = 0x40;
            if (bounds == 0)
                bounds = initial_capacity;
            do
                bounds <<= 2;
            while (bounds < amount);

            abstract_buffer_ptr buffer_new = allocator.buffer_->create(bounds);
            abstract_buffer_ptr buffer_old = std::move(allocator.buffer_);
            if (allocator.offset_ > 0)
                std::memcpy(buffer_new->buffer(), buffer_old->buffer(), allocator.offset_);
            allocator.buffer_ = std::move(buffer_new);
            allocator.bounds_ = bounds;
        }

    public:
        allocator(abstract_buffer_ptr buffer, size_t max_capacity)
        {
            if (buffer == nullptr)
                exceptions::throw_helper::throw_argument_null_exception();
            if (max_capacity > std::numeric_limits<int32_t>::max())
                exceptions::throw_helper::throw_argument_exception();
            buffer_ = buffer;
            offset_ = 0;
            bounds_ = buffer->length();
            limits_ = max_capacity;
        }

        allocator(abstract_buffer_ptr buffer) : allocator(buffer, std::numeric_limits<int32_t>::max()) {}

        allocator(allocator&&) = delete;

        allocator(const allocator&) = delete;

        virtual ~allocator() = default;

        static inline void ensure(allocator& allocator, size_t length)
        {
            assert(length != 0);
            assert(allocator.bounds_ <= allocator.limits_);
            assert(allocator.offset_ <= allocator.bounds_);
            if (allocator.bounds_ - allocator.offset_ >= length)
                return;
            resize(allocator, length);
        }
    };
}
