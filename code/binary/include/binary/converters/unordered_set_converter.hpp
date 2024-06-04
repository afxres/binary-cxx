#pragma once

#include "basic_container_converter.hpp"
#include "basic_counter.hpp"
#include "basic_emplace_adder.hpp"

#include <unordered_set>

namespace mikodev::binary::converters {
template <
    typename T,
    typename Hash = std::hash<T>,
    typename Equal = std::equal_to<T>,
    typename Allocator = std::allocator<T>>
using unordered_set_converter = basic_container_converter<std::unordered_set<T, Hash, Equal, Allocator>, T, basic_emplace_adder, basic_counter>;
}
