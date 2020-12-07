#pragma once

namespace mikodev::binary::converters::containers
{
    template <typename _Container, typename _Element>
    struct _basic_sequence_adder
    {
        static void add(_Container& container, _Element&& item) { container.push_back(std::forward<_Element>(item)); }
    };
}
