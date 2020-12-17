#pragma once

#include "basic_container_converter.hpp"
#include "basic_empty_counter.hpp"
#include "basic_emplace_adder.hpp"

#include <set>

namespace mikodev::binary::converters
{
    template <typename T, typename Compare = std::less<T>, typename Allocator = std::allocator<T>>
    using set_converter = basic_container_converter<std::set<T, Compare, Allocator>, T, basic_emplace_adder, basic_empty_counter>;
}
