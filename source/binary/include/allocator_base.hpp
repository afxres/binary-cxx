#pragma once

namespace mikodev::binary
{
    class allocator_base
    {
    public:
        virtual size_t capacity() const noexcept = 0;

        virtual size_t size() const noexcept = 0;

        virtual std::byte* allocate(size_t size) = 0;

        virtual size_t _make_anchor(size_t size) = 0;

        virtual std::byte* _make_append(size_t anchor, size_t size, size_t& out_offset) = 0;
    };
}
