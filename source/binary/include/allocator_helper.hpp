#pragma once

#include "allocator_base.hpp"
#include "primitive_helper.hpp"

namespace mikodev::binary
{
    using allocator_anchor_t = size_t;

    class allocator_helper
    {
    private:
        allocator_helper() = default;

    public:
        static allocator_anchor_t anchor_length_prefix(allocator_base& allocator)
        {
            return static_cast<allocator_anchor_t>(allocator._make_anchor(sizeof(number_t)));
        }

        static void append_length_prefix(allocator_base& allocator, allocator_anchor_t anchor)
        {
            size_t offset;
            std::byte* location = allocator._make_append(static_cast<size_t>(anchor), sizeof(number_t), offset);
            size_t origin = static_cast<size_t>(anchor) + sizeof(number_t);
            primitive_helper::encode_number_fixed4(location, static_cast<number_t>(offset - origin));
        }
    };
}
