#pragma once

#ifndef BINARY_GENERATOREXTENSIONS_HPP
#define BINARY_GENERATOREXTENSIONS_HPP

#include "Converter.hpp"
#include "IGenerator.hpp"

namespace binary {
template <typename T>
std::shared_ptr<Converter<T>> GetConverter(const IGenerator& generator) {
    return std::dynamic_pointer_cast<Converter<T>>(generator.GetConverter(typeid(T)));
}

template <
    typename TConverter,
    typename... TArguments,
    std::enable_if_t<std::is_base_of_v<IConverter, TConverter>, bool> = true>
void AddConverter(IGenerator& generator) {
    std::shared_ptr<IConverter> converter = std::make_shared<TConverter>(GetConverter<TArguments>(generator)...);
    generator.AddConverter(converter);
}

template <
    template <typename...> typename TConverter,
    typename... TArguments,
    std::enable_if_t<std::is_base_of_v<IConverter, TConverter<TArguments...>>, bool> = true>
void AddConverter(IGenerator& generator) {
    std::shared_ptr<IConverter> converter = std::make_shared<TConverter<TArguments...>>(GetConverter<TArguments>(generator)...);
    generator.AddConverter(converter);
}
}

#endif
