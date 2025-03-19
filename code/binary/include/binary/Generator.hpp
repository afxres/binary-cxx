#ifndef BINARY_GENERATOR_HPP
#define BINARY_GENERATOR_HPP

#include <typeindex>
#include <unordered_map>

#include "binary/IGenerator.hpp"

namespace binary {
class Generator : public IGenerator {
private:
    std::unordered_map<std::type_index, std::shared_ptr<IConverter>> converters;

public:
    virtual void AddConverter(const std::shared_ptr<IConverter>& converter) override;
    virtual std::shared_ptr<IConverter> GetConverter(std::type_index type) const override;
};
}

#endif
