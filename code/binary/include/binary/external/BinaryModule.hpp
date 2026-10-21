#ifndef BINARY_EXTERNAL_BINARYMODULE_HPP
#define BINARY_EXTERNAL_BINARYMODULE_HPP

#include <cstddef>
#include <span>

#include "binary/external/LongDataSlot.hpp"

namespace binary::external {
LongDataSlot GetLongData(std::span<const std::byte> span);
}

#endif
