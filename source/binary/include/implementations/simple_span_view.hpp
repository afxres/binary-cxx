#pragma once

#include "../span_view_base.hpp"
#include "../exceptions/throw_helper.hpp"

#include <memory>

namespace mikodev::binary::implementations
{
    class simple_span_view : public span_view_base
    {
    private:
        std::shared_ptr<byte_t[]> _data;

        size_t _size;

        size_t _offset;

        size_t _length;

        simple_span_view(std::shared_ptr<byte_t[]> data, size_t size, size_t offset, size_t length) : _data(size == 0 ? nullptr : data), _size(size), _offset(offset), _length(length) {}

    public:
        simple_span_view(std::shared_ptr<byte_t[]> data, size_t size) : simple_span_view(data, size, 0, size) {}

        std::shared_ptr<byte_t[]> origin_data() const noexcept { return _data; }

        size_t origin_size() const noexcept { return _size; }

        virtual const byte_t* data() const noexcept override { return &_data[_offset]; }

        virtual size_t size() const noexcept override { return _length; }

        virtual std::unique_ptr<span_view_base> slice(size_t offset) const override
        {
            if (offset > _length)
                exceptions::throw_helper::throw_argument_exception();
            else
                return std::unique_ptr<simple_span_view>(new simple_span_view(_data, _size, _offset + offset, _length - offset));
        }

        virtual std::unique_ptr<span_view_base> slice(size_t offset, size_t length) const override
        {
            if (offset > _length || length > _length - offset)
                exceptions::throw_helper::throw_argument_exception();
            else
                return std::unique_ptr<simple_span_view>(new simple_span_view(_data, _size, _offset + offset, length));
        }

        virtual void slice_this(size_t offset) override
        {
            if (offset > _length)
                exceptions::throw_helper::throw_argument_exception();
            _offset += offset;
            _length -= offset;
        }

        virtual void slice_this(size_t offset, size_t length) override
        {
            if (offset > _length || length > _length - offset)
                exceptions::throw_helper::throw_argument_exception();
            _offset += offset;
            _length = length;
        }
    };
}
