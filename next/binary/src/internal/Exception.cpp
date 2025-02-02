#include "binary/internal/Exception.hpp"

#include <stdexcept>

namespace binary::internal {
void ThrowNotEnoughBytes() {
    throw std::length_error("not enough bytes or byte sequence invalid");
}

void ThrowNotEnoughBytesToWrite() {
    throw std::length_error("not enough bytes to write");
}

void ThrowInvalidBytesWrittenValue() {
    throw std::logic_error("value for bytes written is invalid or not set");
}
}
