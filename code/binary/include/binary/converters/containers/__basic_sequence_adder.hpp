#pragma once

namespace mikodev::binary::converters::containers
{
    template <typename _Container, typename _Element>
    struct __basic_sequence_adder
    {
        static void add(_Container& container, _Element&& item) { container.push_back(std::forward<_Element>(item)); }
    };
}
