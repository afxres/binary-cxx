#pragma once

#include "_basic_container_converter.hpp"
#include "_basic_empty_counter.hpp"
#include "_basic_set_adder.hpp"

#include <set>

namespace mikodev::binary::converters::containers
{
    template <typename _Kty, typename _Pr = std::less<_Kty>, typename _Alloc = std::allocator<_Kty>>
    using set_converter = _basic_container_converter<std::set<_Kty, _Pr, _Alloc>, _Kty, _basic_set_adder, _basic_empty_counter>;
}
