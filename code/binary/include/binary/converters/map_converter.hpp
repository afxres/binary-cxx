#pragma once

#include "basic_pair_container_converter.hpp"

#include <map>

namespace mikodev::binary::converters
{
    template <typename Key, typename Value, typename Compare = std::less<Key>, typename Allocator = std::allocator<std::pair<const Key, Value>>>
    using map_converter = basic_pair_container_converter<std::map<Key, Value, Compare, Allocator>, Key, Value>;
}
