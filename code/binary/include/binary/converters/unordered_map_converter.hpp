#pragma once

#include "basic_pair_container_converter.hpp"

#include <unordered_map>

namespace mikodev::binary::converters {
template <
    typename Key,
    typename Value,
    typename Hash = std::hash<Key>,
    typename Equal = std::equal_to<Key>,
    typename Allocator = std::allocator<std::pair<const Key, Value>>>
using unordered_map_converter = basic_pair_container_converter<std::unordered_map<Key, Value, Hash, Equal, Allocator>, Key, Value>;
}
