#pragma once

#include "__basic_container_converter.hpp"
#include "__basic_counter.hpp"
#include "__basic_set_adder.hpp"

#include <unordered_set>

namespace mikodev::binary::converters::containers
{
    template <typename _Kty, typename _Hasher = std::hash<_Kty>, typename _Keyeq = std::equal_to<_Kty>, typename _Alloc = std::allocator<_Kty>>
    using unordered_set_converter = __basic_container_converter<std::unordered_set<_Kty, _Hasher, _Keyeq, _Alloc>, _Kty, __basic_set_adder, __basic_counter>;
}
