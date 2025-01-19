#ifndef BINARY_IGENERATOR_HPP
#define BINARY_IGENERATOR_HPP

#include <memory>

#include "binary/IConverter.hpp"

namespace binary {
class IGenerator {
public:
    virtual void AddConverter(std::shared_ptr<IConverter> converter) = 0;
    virtual std::shared_ptr<IConverter> GetConverter(std::type_index type) const = 0;
};
}

#endif
