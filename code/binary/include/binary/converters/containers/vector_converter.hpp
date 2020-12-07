#pragma once

#include "_basic_container_converter.hpp"
#include "_basic_counter.hpp"
#include "_basic_sequence_adder.hpp"

#include <vector>

namespace mikodev::binary::converters::containers
{
    template <typename _Ty, typename _Alloc = std::allocator<_Ty>>
    using vector_converter = _basic_container_converter<std::vector<_Ty, _Alloc>, _Ty, _basic_sequence_adder, _basic_counter>;
}
