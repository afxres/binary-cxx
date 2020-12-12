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

        size_t offset_;

        size_t bounds_;

        size_t limits_;

        static void resize__(allocator& allocator, size_t length)
        {
            assert(allocator.bounds_ <= allocator.shared_->length());
            assert(allocator.limits_ <= number::max_supported_size);
            assert(allocator.bounds_ <= number::max_supported_size);
            assert(allocator.offset_ <= allocator.bounds_);
            if (length == 0 || length > number::max_supported_size)
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

        static size_t anchor__(allocator& allocator, size_t length)
        {
            ensure(allocator, length);
            size_t offset = allocator.offset_;
            allocator.offset_ = offset + length;
            return offset;
        }

        static byte_ptr assign__(allocator& allocator, size_t length)
        {
            assert(length != 0);
            size_t offset = anchor__(allocator, length);
            return allocator.buffer_ + offset;
        }

        static void finish_anchor__(allocator& allocator, size_t anchor)
        {
            assert(anchor <= number::max_supported_size - 4);
            const size_t limits = 16;
            size_t offset = allocator.offset_;
            int64_t result = static_cast<int64_t>(offset) - static_cast<int64_t>(anchor) - 4;
            if (result < 0)
                exceptions::throw_helper::throw_allocator_modified();
            uint32_t length = static_cast<uint32_t>(result);
            byte_ptr target = allocator.buffer_ + anchor;
            if (length <= limits && allocator.bounds_ - offset >= static_cast<size_t>((-static_cast<int32_t>(length)) & 7))
            {
                allocator.offset_ = offset - 3;
                number::encode(target, static_cast<number_t>(length), 1);
                std::memmove(target + 1, target + 4, static_cast<size_t>(length));
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
        allocator(abstract_buffer_ptr shared, size_t max_capacity)
        {
            if (shared == nullptr)
                exceptions::throw_helper::throw_argument_null_exception();
            if (max_capacity > number::max_supported_size)
                exceptions::throw_helper::throw_argument_out_of_range_exception();
            buffer_ = shared->buffer();
            bounds_ = shared->length();
            shared_ = shared;
            offset_ = 0;
            limits_ = max_capacity;
        }

        allocator(abstract_buffer_ptr shared) : allocator(shared, number::max_supported_size) {}

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
            resize__(allocator, length);
        }

        static inline void expand(allocator& allocator, size_t length)
        {
            ensure(allocator, length);
            allocator.offset_ += length;
        }
    };
}
