#pragma once

#include "../allocator_base.hpp"
#include "../exceptions/throw_helper.hpp"
#include "simple_allocator_dump.hpp"

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

        size_t _capacity;

        void expand_capacity(size_t size)
        {
            const size_t initial_capacity = 0x80;
            const size_t maximum_capacity = 0x4000'0000;

            assert(size != 0);
            size_t capacity = _capacity;
            uintmax_t amount = capacity + size;
            if (amount >= maximum_capacity)
                exceptions::throw_helper::throw_capacity_limited();

            if (capacity == 0)
                capacity = initial_capacity;
            do
                capacity *= 2;
            while (capacity < amount);

            std::shared_ptr<byte_t[]> new_data(new byte_t[capacity]);
            std::shared_ptr<byte_t[]> old_data = std::move(_data);
            if (_offset != 0)
                std::memcpy(&new_data[0], &old_data[0], _offset);
            _data = std::move(new_data);
            _capacity = capacity;
        }

        inline void ensure_capacity(size_t size)
        {
            assert(size != 0);
            if (_capacity - _offset >= size)
                return;
            expand_capacity(size);
        }

    public:
        simple_allocator() noexcept : _data(nullptr), _offset(0), _capacity(0) {}

        simple_allocator_dump dump() { return simple_allocator_dump(_data, _offset, _capacity); }

        virtual size_t capacity() const noexcept { return _capacity; };

        virtual size_t size() const noexcept { return _offset; }

    protected:
        virtual byte_t* _allocate(size_t size) override
        {
            assert(size != 0);
            ensure_capacity(size);
            size_t origin = _offset;
            _offset = origin + size;
            return &_data[origin];
        }

        virtual byte_t* _allocate_without_increase_offset(size_t size) override
        {
            assert(size != 0);
            ensure_capacity(size);
            return &_data[_offset];
        }

        virtual void _increase_offset(size_t size) override
        {
            assert(size != 0);
            assert(_capacity > _offset);
            assert(_capacity - _offset >= size);
            _offset += size;
        }

        virtual size_t _make_anchor(size_t size) override
        {
            assert(size != 0);
            size_t offset = _offset;
            ensure_capacity(size);
            _offset = offset + size;
            return offset;
        }

        virtual byte_t* _make_append(size_t anchor, size_t size, size_t& out_offset) override
        {
            assert(size != 0);
            size_t offset = _offset;
            if (anchor > offset || size > offset - anchor)
                exceptions::throw_helper::throw_argument_exception();
            out_offset = offset;
            return &_data[anchor];
        }
    };
}
