#pragma once

#include "../allocator_base.hpp"
#include "../primitive_helper.hpp"
#include "../exceptions/throw_helper.hpp"

#include "simple_span_view.hpp"

#include <cmath>
#include <memory>
#include <cassert>

namespace mikodev::binary::implementations
{
    /* simple memory allocator (thread unsafe) */
    class simple_allocator : public mikodev::binary::allocator_base
    {
    private:
        std::shared_ptr<byte_t[]> _data;

        size_t _offset;

        size_t _bounds;

        size_t _max_capacity;

        void expand_capacity(size_t size)
        {

            assert(size != 0);
            size_t bounds = _bounds;
            uintmax_t amount = bounds + size;
            if (amount >= _max_capacity)
                exceptions::throw_helper::throw_capacity_limited();

            const size_t initial_capacity = 0x40;
            if (bounds == 0)
                bounds = initial_capacity;
            do
                bounds <<= 2;
            while (bounds < amount);

            std::shared_ptr<byte_t[]> new_data(new byte_t[bounds]);
            std::shared_ptr<byte_t[]> old_data = std::move(_data);
            if (_offset != 0)
                std::memcpy(&new_data[0], &old_data[0], _offset);
            _data = std::move(new_data);
            _bounds = bounds;
        }

        inline void ensure_capacity(size_t size)
        {
            assert(size != 0);
            assert(_bounds <= _max_capacity);
            assert(_offset <= _bounds);
            if (_bounds - _offset >= size)
                return;
            expand_capacity(size);
        }

    public:
        simple_allocator() : simple_allocator(nullptr, 0, INT32_MAX) {}

        simple_allocator(std::shared_ptr<byte_t[]> data, size_t capacity, size_t max_capacity)
        {
            if ((data == nullptr && capacity != 0) || max_capacity > INT32_MAX)
                exceptions::throw_helper::throw_argument_exception();
            _data = data;
            _max_capacity = max_capacity;
            _offset = 0;
            _bounds = std::min(capacity, max_capacity);
        }

        std::shared_ptr<byte_t[]> data() const noexcept { return _data; }

        size_t size() const noexcept { return _offset; }

        size_t capacity() const noexcept { return _bounds; };

        size_t max_capacity() const noexcept { return _max_capacity; }

        simple_span_view as_span_view() const noexcept { return simple_span_view(_data, _offset); }

    protected:
        virtual auto assign(size_t size)->byte_t* override
        {
            assert(size != 0);
            ensure_capacity(size);
            size_t origin = _offset;
            _offset = origin + size;
            return &_data[origin];
        }

        virtual auto anchor_length_prefix()->size_t override
        {
            size_t offset = _offset;
            ensure_capacity(sizeof(number_t));
            _offset = offset + sizeof(number_t);
            return offset;
        }

        virtual void append_length_prefix(size_t anchor) override
        {
            size_t offset = _offset;
            if (anchor > offset || sizeof(number_t) > offset - anchor)
                exceptions::throw_helper::throw_argument_exception();
            size_t length = offset - anchor - sizeof(number_t);
            assert(length >= 0);
            byte_t* target = &_data[anchor];
            const size_t limits = 32;
            if (length < limits)
            {
                if (length > 0)
                    std::memmove(target + sizeof(byte_t), target + sizeof(number_t), length);
                *target = static_cast<byte_t>(length);
                _offset = offset - (sizeof(number_t) - sizeof(byte_t));
            }
            else
            {
                primitive_helper::encode_number(&_data[anchor], 4, length);
            }
        }
    };
}
