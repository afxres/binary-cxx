#pragma once

#include "span_view_base.hpp"

namespace mikodev::binary
{
    /* allocator interface */
    class allocator_base
    {
        friend class allocator_helper;

        friend class primitive_helper;

    protected:
        virtual auto assign(size_t size)->byte_t* = 0;

        virtual auto anchor_length_prefix()->size_t = 0;

        virtual void append_length_prefix(size_t anchor) = 0;

    public:
        virtual ~allocator_base() {}
    };
}
