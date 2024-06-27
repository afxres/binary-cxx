#pragma once

#ifndef BINARY_ICONVERTER_HPP
#define BINARY_ICONVERTER_HPP

#include <cstdint>

namespace binary {
class IConverter {
private:
    int32_t length;

public:
    IConverter();
    IConverter(int32_t length);
    virtual ~IConverter() = 0;

    int32_t Length() const {
        return this->length;
    }
};
}

#endif
