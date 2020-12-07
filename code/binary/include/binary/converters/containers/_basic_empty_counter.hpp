#pragma once

#include "../../converter_base.hpp"
#include "../../span_view_base.hpp"

namespace mikodev::binary::converters::containers
{
    template <typename _Container, typename _Element>
    struct _basic_empty_counter
    {
        static void reserve(_Container& container, const converter_base<_Element>& converter, const span_view_base& span)
        {
            // do nothing
        }
    };
}
