#pragma once

#ifndef BINARY_GENERATOR_HPP
#define BINARY_GENERATOR_HPP

#include <map>
#include <typeindex>

#include "binary/IGenerator.hpp"

namespace binary {
class Generator : public IGenerator {
private:
    std::map<std::type_index, std::shared_ptr<IConverter>> converters;

public:
    virtual void AddConverter(std::shared_ptr<IConverter> converter) override;
    virtual std::shared_ptr<IConverter> GetConverter(std::type_index type) const override;
};
}

#endif
