#pragma once

namespace mikodev::binary
{
    /* allocator interface */
    class allocator_base
    {
        friend class allocator_helper;

        friend class primitive_helper;

    protected:
        virtual std::byte* _allocate(size_t size) = 0;

        virtual std::byte* _allocate_without_increase_offset(size_t size) = 0;

        virtual void _increase_offset(size_t size) = 0;

        virtual size_t _make_anchor(size_t size) = 0;

        virtual std::byte* _make_append(size_t anchor, size_t size, size_t& out_offset) = 0;
    };
}
