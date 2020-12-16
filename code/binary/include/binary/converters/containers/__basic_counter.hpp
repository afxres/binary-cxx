#pragma once

#include "../../abstract_converter.hpp"

namespace mikodev::binary::converters::containers
{
    template <typename _Container, typename _Element>
    struct __basic_counter
    {
        static void reserve(_Container& container, const abstract_converter<_Element>& converter, const span& span)
        {
            length_t length = converter.length();
            if (length == 0)
                return;
            length_t capacity = span.length() / length;
            container.reserve(capacity);
        }
    };
}
