#pragma once

#include <cstddef>
#include <cstdint>
#include <limits>

namespace mikodev::binary
{
    using byte_t = std::byte;

    using byte_ptr = byte_t*;

    using const_byte_ptr = const byte_t*;

    using length_t = uint32_t;

    const length_t length_max = static_cast<length_t>(std::numeric_limits<int32_t>::max());
}
