#pragma once

#include "_basic_container_converter.hpp"
#include "_basic_empty_counter.hpp"
#include "_basic_set_adder.hpp"

#include <map>

namespace mikodev::binary::converters::containers
{
    template <typename _Kty, typename _Ty, typename _Pr = std::less<_Kty>, typename _Alloc = std::allocator<std::pair<const _Kty, _Ty>>>
    using map_converter = _basic_pair_container_converter<std::map<_Kty, _Ty, _Pr, _Alloc>, _Kty, _Ty>;
}
