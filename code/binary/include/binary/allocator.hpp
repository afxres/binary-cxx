#pragma once

#include "abstract_buffer.hpp"
#include "exceptions/throw_helper.hpp"

#include <cassert>
#include <cstring>

namespace mikodev::binary
{
    class allocator final
    {
    private:
        static const size_t max_supported_capacity = static_cast<size_t>(std::numeric_limits<int32_t>::max());

        abstract_buffer_ptr shared_;

        byte_ptr buffer_;

        size_t offset_;

        size_t bounds_;

        size_t limits_;

        static void resize(allocator& allocator, size_t length)
        {
            assert(allocator.bounds_ <= allocator.shared_->length());
            assert(allocator.limits_ <= max_supported_capacity);
            assert(allocator.bounds_ <= max_supported_capacity);
            assert(allocator.offset_ <= allocator.bounds_);
            if (length == 0 || length > max_supported_capacity)
                exceptions::throw_helper::throw_argument_out_of_range_exception();
            size_t offset = allocator.offset_;
            size_t limits = allocator.limits_;
            size_t amount = offset + length;
            if (amount > limits)
                exceptions::throw_helper::throw_capacity_limited();

            size_t cursor = allocator.bounds_;
            const size_t initial = 64;
            if (cursor == 0)
                cursor = initial;
            do
                cursor <<= 2;
            while (cursor < amount);
            if (cursor > limits)
                cursor = limits;
            assert(amount <= cursor);
            assert(cursor <= limits);

            abstract_buffer_ptr buffer_new = allocator.shared_->create(cursor);
            abstract_buffer_ptr buffer_old = std::move(allocator.shared_);
            if (offset > 0)
                std::memcpy(buffer_new->buffer(), buffer_old->buffer(), offset);
            allocator.buffer_ = buffer_new->buffer();
            allocator.shared_ = buffer_new;
            allocator.bounds_ = cursor;
        }

    public:
        allocator(abstract_buffer_ptr shared, size_t max_capacity)
        {
            if (shared == nullptr)
                exceptions::throw_helper::throw_argument_null_exception();
            if (max_capacity > max_supported_capacity)
                exceptions::throw_helper::throw_argument_out_of_range_exception();
            buffer_ = shared->buffer();
            bounds_ = shared->length();
            shared_ = shared;
            offset_ = 0;
            limits_ = max_capacity;
        }

        allocator(abstract_buffer_ptr shared) : allocator(shared, max_supported_capacity) {}

        size_t length() const noexcept { return offset_; }

        size_t capacity() const noexcept { return bounds_; }

        size_t max_capacity() const noexcept { return limits_; }

        static inline void ensure(allocator& allocator, size_t length)
        {
            assert(length != 0);
            assert(allocator.bounds_ <= allocator.limits_);
            assert(allocator.offset_ <= allocator.bounds_);
            if (allocator.bounds_ - allocator.offset_ >= length)
                return;
            resize(allocator, length);
        }

        static inline void expand(allocator& allocator, size_t length)
        {
            ensure(allocator, length);
            allocator.offset_ += length;
        }
    };
}
