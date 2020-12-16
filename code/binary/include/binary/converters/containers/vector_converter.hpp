#pragma once

#include "__basic_container_converter.hpp"
#include "__basic_counter.hpp"
#include "__basic_sequence_adder.hpp"

#include <vector>

namespace mikodev::binary::converters::containers
{
    template <typename _Ty, typename _Alloc = std::allocator<_Ty>>
    using vector_converter = __basic_container_converter<std::vector<_Ty, _Alloc>, _Ty, __basic_sequence_adder, __basic_counter>;
}
