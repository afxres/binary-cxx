#include "binary/internal/Module.hpp"

#include <cassert>
#include <format>
#include <stdexcept>

namespace binary::internal {
size_t GetCapacity(size_t byteLength, size_t itemLength, std::type_index type) {
    assert(byteLength != 0);
    assert(itemLength != 0);
    if ((byteLength % itemLength) != 0) {
        throw std::length_error(std::format("not enough bytes or byte sequence invalid, byte length: {}, type: {}", byteLength, type.name()));
    }
    return byteLength / itemLength;
}
}
