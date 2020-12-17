#pragma once

#include "basic_container_converter.hpp"
#include "basic_counter.hpp"
#include "basic_push_back_adder.hpp"

#include <vector>

namespace mikodev::binary::converters
{
    template <typename T, typename Allocator = std::allocator<T>>
    using vector_converter = basic_container_converter<std::vector<T, Allocator>, T, basic_push_back_adder, basic_counter>;
}
