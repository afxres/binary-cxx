#pragma once

namespace mikodev::binary::converters::containers
{
    template <typename _Container, typename _Element>
    struct _basic_set_adder
    {
        static void add(_Container& container, _Element&& item) { container.insert(item); }
    };
}
