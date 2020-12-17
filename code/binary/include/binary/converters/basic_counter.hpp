#pragma once

#include "../abstract_converter.hpp"

namespace mikodev::binary::converters
{
    template <typename Container, typename Element>
    struct basic_counter
    {
        static void reserve(Container& container, const abstract_converter<Element>& converter, const span& span)
        {
            length_t length = converter.length();
            if (length == 0)
                return;
            length_t capacity = span.length() / length;
            container.reserve(capacity);
        }
    };
}
