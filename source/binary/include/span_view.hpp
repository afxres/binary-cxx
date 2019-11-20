#pragma once

#include "span_view_base.hpp"
#include "exceptions/throw_helper.hpp"

namespace mikodev::binary
{
    /* readonly memory view (immutable) */
    class span_view
    {
    private:
        const byte_t* _data;

        size_t _size;

    public:
        span_view() noexcept : span_view(nullptr, 0) {}

        span_view(const byte_t* data, size_t size) noexcept : _data(size == 0 ? nullptr : data), _size(size) {}

        const byte_t* data() const noexcept { return _data; }

        size_t size() const noexcept { return _size; }

        span_view slice(size_t offset) const
        {
            if (offset > _size)
                exceptions::throw_helper::throw_argument_exception();
            else
                return span_view(_data + offset, _size - offset);
        }

        span_view slice(size_t offset, size_t length) const
        {
            if (offset > _size || length > _size - offset)
                exceptions::throw_helper::throw_argument_exception();
            else
                return span_view(_data + offset, length);
        }
    };
}
