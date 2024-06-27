#pragma once

#ifndef BINARY_ICONVERTER_HPP
#define BINARY_ICONVERTER_HPP

#include <cstdint>
#include <typeindex>

namespace binary {
class IConverter {
private:
    std::type_index argument;
    int32_t length;

public:
    IConverter(std::type_index argument);
    IConverter(std::type_index argument, int32_t length);
    virtual ~IConverter() = 0;

    std::type_index GetGenericArgument() const {
        return this->argument;
    }

    int32_t Length() const {
        return this->length;
    }
};
}

#endif
