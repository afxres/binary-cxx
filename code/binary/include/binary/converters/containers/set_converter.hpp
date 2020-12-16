#pragma once

#include "__basic_container_converter.hpp"
#include "__basic_empty_counter.hpp"
#include "__basic_set_adder.hpp"

#include <set>

namespace mikodev::binary::converters::containers
{
    template <typename _Kty, typename _Pr = std::less<_Kty>, typename _Alloc = std::allocator<_Kty>>
    using set_converter = __basic_container_converter<std::set<_Kty, _Pr, _Alloc>, _Kty, __basic_set_adder, __basic_empty_counter>;
}
