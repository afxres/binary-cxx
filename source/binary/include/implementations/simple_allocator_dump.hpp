#pragma once

#include "../span_view.hpp"

#include <memory>

namespace mikodev::binary::implementations
{
    class simple_allocator_dump
    {
    private:
        std::shared_ptr<byte_t[]> _data;

        size_t _offset;

        size_t _capacity;

    public:
        simple_allocator_dump(std::shared_ptr<byte_t[]> data, size_t offset, size_t capacity) : _data(data), _offset(offset), _capacity(capacity) {}

        std::shared_ptr<byte_t[]> data() const noexcept { return _data; }

        size_t capacity() const noexcept { return _capacity; };

        size_t size() const noexcept { return _offset; }

        mikodev::binary::span_view as_span_view() const noexcept { return  mikodev::binary::span_view(_offset == 0 ? nullptr : &_data[0], _offset); }
    };
}
