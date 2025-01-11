#pragma once

#ifndef BINARY_CONVERTEREXTENSIONS_HPP
#define BINARY_CONVERTEREXTENSIONS_HPP

#include <format>
#include <memory>

#include "Converter.hpp"

namespace binary {
template <typename T>
std::shared_ptr<Converter<T>> GetConverter(std::shared_ptr<IConverter> converter) {
    std::shared_ptr<Converter<T>> result = std::dynamic_pointer_cast<Converter<T>>(converter);
    if (result == nullptr) {
        std::string source = converter == nullptr ? "source is null" : std::format("source argument type: '{}'", converter->GetGenericArgument().name());
        std::string output = std::format("cast converter pointer error, {}, target argument type: '{}'", source, typeid(T).name());
        throw std::invalid_argument(output);
    }
    return result;
}
}

#endif
