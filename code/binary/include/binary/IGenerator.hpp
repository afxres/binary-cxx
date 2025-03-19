#ifndef BINARY_IGENERATOR_HPP
#define BINARY_IGENERATOR_HPP

#include <memory>

#include "binary/IConverter.hpp"

namespace binary {
class IGenerator {
public:
    virtual ~IGenerator() = 0;
    virtual void AddConverter(const std::shared_ptr<IConverter>& converter) = 0;
    virtual std::shared_ptr<IConverter> GetConverter(std::type_index type) const = 0;
};
}

#endif
