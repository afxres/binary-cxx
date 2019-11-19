#pragma once

#include "exceptions/throw_helper.hpp"

#include <cstddef>

namespace mikodev::binary
{
    /* readonly memory view (immutable) */
    class span_view
    {
    private:
        const std::byte* _data;

        size_t _size;

    public:
        span_view() noexcept : span_view(nullptr, 0) {}

        span_view(const std::byte* data, size_t size) noexcept : _data(size == 0 ? nullptr : data), _size(size) {}

        const std::byte* data() const noexcept { return _data; }

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
