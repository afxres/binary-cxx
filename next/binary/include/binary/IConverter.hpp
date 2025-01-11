#pragma once

#ifndef BINARY_ICONVERTER_HPP
#define BINARY_ICONVERTER_HPP

#include <cstddef>
#include <typeindex>

namespace binary {
class IConverter {
private:
    std::type_index argument;
    size_t length;

public:
    IConverter(std::type_index argument);
    IConverter(std::type_index argument, size_t length);
    virtual ~IConverter() = 0;

    std::type_index GetGenericArgument() const {
        return this->argument;
    }

    size_t Length() const {
        return this->length;
    }
};
}

#endif
