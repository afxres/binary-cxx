#include "binary/IConverter.hpp"

#include <cassert>
#include <stdexcept>

namespace binary {
IConverter::IConverter(std::type_index argument)
    : argument(argument) {
    this->length = 0;
}

IConverter::IConverter(std::type_index argument, int32_t length)
    : argument(argument) {
    if (length < 0) {
        throw std::out_of_range("length < 0");
    }
    this->length = length;
}

IConverter::~IConverter() {}
}
