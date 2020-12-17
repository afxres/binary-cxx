#pragma once

namespace mikodev::binary::converters
{
    template <typename Container, typename Element>
    struct basic_push_back_adder
    {
        static void add(Container& container, Element&& item) { container.push_back(std::forward<Element>(item)); }
    };
}
