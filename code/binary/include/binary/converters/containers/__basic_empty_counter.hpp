#pragma once

#include "../../abstract_converter.hpp"

namespace mikodev::binary::converters::containers
{
    template <typename _Container, typename _Element>
    struct __basic_empty_counter
    {
        static void reserve(_Container& container, const abstract_converter<_Element>& converter, const span& span) {}
    };
}
