#ifndef BINARY_INTERNAL_CONTAINER_HPP
#define BINARY_INTERNAL_CONTAINER_HPP

#include <cassert>
#include <cstddef>
#include <format>
#include <stdexcept>

namespace binary::internal {
template <typename T>
size_t GetCapacity(size_t byteLength, size_t itemLength) {
    assert(byteLength != 0);
    assert(itemLength != 0);
    if ((byteLength % itemLength) != 0) {
        throw std::length_error(std::format("not enough bytes for container element, byte length: {}, element type: {}", byteLength, typeid(T).name()));
    }
    return byteLength / itemLength;
}
}

#endif
