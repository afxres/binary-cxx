#pragma once

namespace mikodev::binary::converters
{
    template <typename Container, typename Element>
    struct basic_emplace_adder
    {
        static void add(Container& container, Element&& item) { container.emplace(std::forward<Element>(item)); }
    };
}
