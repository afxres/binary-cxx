#ifndef BINARY_ICONVERTER_HPP
#define BINARY_ICONVERTER_HPP

#include <cstddef>
#include <typeindex>

namespace binary {
class IConverter {
private:
    const std::type_index type;
    const size_t length;

public:
    size_t Length() const { return this->length; }
    std::type_index GetConverterType() const { return this->type; }

    IConverter(std::type_index type);
    IConverter(std::type_index type, size_t length);
    virtual ~IConverter() = 0;
};
}

#endif
