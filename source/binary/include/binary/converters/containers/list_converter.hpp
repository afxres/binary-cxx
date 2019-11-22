#pragma once

#include "_basic_container_converter.hpp"
#include "_basic_sequence_adder.hpp"

#include <list>

namespace mikodev::binary::converters::containers
{
    template <typename _Ty, typename _Alloc = std::allocator<_Ty>>
    using list_converter = _basic_container_converter<std::list<_Ty, _Alloc>, _Ty, _basic_sequence_adder>;
}
