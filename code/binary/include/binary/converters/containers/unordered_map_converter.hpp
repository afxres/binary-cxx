#pragma once

#include "__basic_pair_container_converter.hpp"

#include <unordered_map>

namespace mikodev::binary::converters::containers
{
    template <typename _Kty, typename _Ty, typename _Hasher = std::hash<_Kty>, typename _Keyeq = std::equal_to<_Kty>, typename _Alloc = std::allocator<std::pair<const _Kty, _Ty>>>
    using unordered_map_converter = __basic_pair_container_converter<std::unordered_map<_Kty, _Ty, _Hasher, _Keyeq, _Alloc>, _Kty, _Ty>;
}
