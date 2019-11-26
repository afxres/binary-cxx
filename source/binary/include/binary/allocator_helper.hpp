#pragma once

#include "allocator_base.hpp"
#include "primitive_helper.hpp"
#include "exceptions/throw_helper.hpp"

namespace mikodev::binary
{
    using allocator_length_prefix_anchor_t = size_t;

    template <typename T>
    using allocator_action_t = void (*)(byte_t * data, size_t size, const T & item);

    class allocator_helper
    {
    private:
        allocator_helper() = delete;

    public:
        static allocator_length_prefix_anchor_t anchor_length_prefix(allocator_base& allocator)
        {
            return static_cast<allocator_length_prefix_anchor_t>(allocator._make_anchor(sizeof(number_t)));
        }

        static void append_length_prefix(allocator_base& allocator, allocator_length_prefix_anchor_t anchor)
        {
            size_t offset;
            byte_t* location = allocator._make_append(static_cast<size_t>(anchor), sizeof(number_t), offset);
            size_t origin = static_cast<size_t>(anchor) + sizeof(number_t);
            primitive_helper::encode_number_fixed4(location, static_cast<number_t>(offset - origin));
        }

        static void append(allocator_base& allocator, const void* data, size_t size)
        {
            if (size == 0)
                return;
            byte_t* location = allocator._allocate(size);
            std::memcpy(location, data, size);
        }

        template <typename T>
        static void append(allocator_base& allocator, size_t size, const T& item, allocator_action_t<T> action)
        {
            if (action == nullptr)
                exceptions::throw_helper::throw_argument_exception();
            if (size == 0)
                return;
            byte_t* data = allocator._allocate_without_increase_offset(size);
            action(data, size, item);
            allocator._increase_offset(size);
        }
    };
}
