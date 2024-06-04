#pragma once

#include "../abstract_converter.hpp"

namespace mikodev::binary::converters {
template <typename Container, typename Element>
struct basic_empty_counter {
    static void reserve(Container& container, const abstract_converter<Element>& converter, const span& span) {}
};
}
