#pragma once

#include "basic_container_converter.hpp"
#include "basic_empty_counter.hpp"
#include "basic_push_back_adder.hpp"

#include <deque>

namespace mikodev::binary::converters
{
    template <typename Container, typename Allocator = std::allocator<Container>>
    using deque_converter = basic_container_converter<std::deque<Container, Allocator>, Container, basic_push_back_adder, basic_empty_counter>;
}
