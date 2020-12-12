#pragma once

#include "abstract_buffer.hpp"
#include "number.hpp"
#include "exceptions/throw_helper.hpp"

#include <cassert>
#include <cstring>

namespace mikodev::binary
{
    class allocator final
    {
        friend class converter;

    private:
        abstract_buffer_ptr shared_;

        byte_ptr buffer_;

        length_t offset_;

        length_t bounds_;

        length_t limits_;

        static void resize__(allocator& allocator, length_t length)
        {
            assert(allocator.bounds_ <= allocator.shared_->length());
            assert(allocator.limits_ <= length_max);
            assert(allocator.bounds_ <= length_max);
            assert(allocator.offset_ <= allocator.bounds_);
            if (length == 0)
                exceptions::throw_helper::throw_argument_out_of_range_exception();
            length_t offset = allocator.offset_;
            length_t limits = allocator.limits_;
            uint64_t amount = static_cast<uint64_t>(offset) + static_cast<uint64_t>(length);
            if (amount > limits)
                exceptions::throw_helper::throw_capacity_limited();

            uint64_t cursor = static_cast<uint64_t>(allocator.bounds_);
            const length_t initial = 64;
            if (cursor == 0)
                cursor = initial;
            do
                cursor <<= 2;
            while (cursor < amount);
            if (cursor > limits)
                cursor = limits;
            assert(amount <= cursor);
            assert(cursor <= limits);

            abstract_buffer_ptr buffer_new = allocator.shared_->create(static_cast<length_t>(cursor));
            abstract_buffer_ptr buffer_old = std::move(allocator.shared_);
            if (offset > 0)
                std::memcpy(buffer_new->buffer(), buffer_old->buffer(), offset);
            allocator.buffer_ = buffer_new->buffer();
            allocator.bounds_ = buffer_new->length();
            allocator.shared_ = buffer_new;
        }

        static length_t anchor__(allocator& allocator, length_t length)
        {
            ensure(allocator, length);
            length_t offset = allocator.offset_;
            allocator.offset_ = offset + length;
            return offset;
        }

        static byte_ptr assign__(allocator& allocator, length_t length)
        {
            assert(length != 0);
            length_t offset = anchor__(allocator, length);
            return allocator.buffer_ + offset;
        }

        static void finish_anchor__(allocator& allocator, length_t anchor)
        {
            assert(anchor <= length_max - 4);
            const length_t limits = 16;
            length_t offset = allocator.offset_;
            if (offset < anchor + 4)
                exceptions::throw_helper::throw_allocator_modified();
            length_t length = offset - anchor - 4;
            byte_ptr target = allocator.buffer_ + anchor;
            if (length <= limits && allocator.bounds_ - offset >= static_cast<length_t>((-static_cast<int32_t>(length)) & 7))
            {
                allocator.offset_ = offset - 3;
                number::encode(target, static_cast<number_t>(length), 1);
                std::memmove(target + 1, target + 4, length);
                assert(allocator.offset_ >= 1);
                assert(allocator.offset_ <= allocator.bounds_);
            }
            else
            {
                number::encode(target, static_cast<number_t>(length), 4);
                assert(allocator.offset_ >= 1);
                assert(allocator.offset_ <= allocator.bounds_);
            }
        }

    public:
        allocator(abstract_buffer_ptr shared, length_t max_capacity)
        {
            if (shared == nullptr)
                exceptions::throw_helper::throw_argument_null_exception();
            if (max_capacity > length_max)
                exceptions::throw_helper::throw_argument_out_of_range_exception();
            buffer_ = shared->buffer();
            bounds_ = shared->length();
            shared_ = shared;
            offset_ = 0;
            limits_ = max_capacity;
        }

        allocator(abstract_buffer_ptr shared) : allocator(shared, length_max) {}

        length_t length() const noexcept { return offset_; }

        length_t capacity() const noexcept { return bounds_; }

        length_t max_capacity() const noexcept { return limits_; }

        static inline void ensure(allocator& allocator, length_t length)
        {
            assert(length != 0);
            assert(allocator.bounds_ <= allocator.limits_);
            assert(allocator.offset_ <= allocator.bounds_);
            if (allocator.bounds_ - allocator.offset_ >= length)
                return;
            resize__(allocator, length);
        }

        static inline void expand(allocator& allocator, length_t length)
        {
            ensure(allocator, length);
            allocator.offset_ += length;
        }
    };
}
