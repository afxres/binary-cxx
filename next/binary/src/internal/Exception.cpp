#include "binary/internal/Exception.hpp"

#include <format>
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

void ThrowInvalidConverterType(std::type_index source, std::type_index target) {
    std::string intent = source == typeid(nullptr) ? "source is null" : std::format("source argument type: '{}'", source.name());
    std::string output = std::format("cast converter pointer error, {}, target argument type: '{}'", intent, target.name());
    throw std::invalid_argument(output);
}
}
