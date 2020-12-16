#pragma once

#include "__basic_container_converter.hpp"
#include "__basic_empty_counter.hpp"
#include "__basic_sequence_adder.hpp"

#include <list>

namespace mikodev::binary::converters::containers
{
    template <typename _Ty, typename _Alloc = std::allocator<_Ty>>
    using list_converter = __basic_container_converter<std::list<_Ty, _Alloc>, _Ty, __basic_sequence_adder, __basic_empty_counter>;
}
