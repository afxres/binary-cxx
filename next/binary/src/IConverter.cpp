#include "binary/IConverter.hpp"

#include <stdexcept>

namespace binary {
IConverter::IConverter() {
    this->length = 0;
}

IConverter::IConverter(int32_t length) {
    if (length < 0) {
        throw std::out_of_range("length < 0");
    }
    this->length = length;
}

IConverter::~IConverter() {}
}
