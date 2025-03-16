#include "binary/IConverter.hpp"

#include <cstdint>
#include <stdexcept>

namespace binary {
IConverter::IConverter(std::type_index type)
    : type(type)
    , length(0) {}

IConverter::IConverter(std::type_index type, size_t length)
    : type(type)
    , length(length) {
    if (length > INT32_MAX) {
        throw std::out_of_range("length > INT32_MAX");
    }
}

IConverter::~IConverter() {}
}
