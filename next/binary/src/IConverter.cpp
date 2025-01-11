#include "binary/IConverter.hpp"

#include <cassert>
#include <cstdint>
#include <stdexcept>

namespace binary {
IConverter::IConverter(std::type_index argument)
    : argument(argument) {
    this->length = 0;
}

IConverter::IConverter(std::type_index argument, size_t length)
    : argument(argument) {
    if (length > INT32_MAX) {
        throw std::out_of_range("length > INT32_MAX");
    }
    this->length = length;
}

IConverter::~IConverter() {}
}
