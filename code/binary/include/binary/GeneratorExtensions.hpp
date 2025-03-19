#ifndef BINARY_GENERATOREXTENSIONS_HPP
#define BINARY_GENERATOREXTENSIONS_HPP

#include "binary/Converter.hpp"
#include "binary/IGenerator.hpp"
#include "binary/internal/Converter.hpp"
#include "binary/internal/ConverterCreateFunction.hpp"

namespace binary {
template <typename T>
    requires std::same_as<T, std::remove_cv_t<T>>
std::shared_ptr<Converter<T>> GetConverter(const IGenerator& generator) {
    return internal::GetConverter<T>(generator.GetConverter(typeid(T)));
}

template <typename TConverter>
    requires requires(const IGenerator& generator) { internal::ConverterCreateFunction<TConverter>()(generator); }
auto CreateConverter(const IGenerator& generator) {
    return internal::ConverterCreateFunction<TConverter>()(generator);
}

template <typename TConverter>
    requires requires(const IGenerator& generator) { CreateConverter<TConverter>(generator); }
void AddConverter(IGenerator& generator) {
    std::shared_ptr<IConverter> converter = CreateConverter<TConverter>(generator);
    generator.AddConverter(converter);
}

template <typename TConverter, typename... TArguments>
    requires std::derived_from<TConverter, IConverter> && std::constructible_from<TConverter, const std::shared_ptr<Converter<TArguments>>&...>
void AddConverter(IGenerator& generator) {
    std::shared_ptr<IConverter> converter = std::make_shared<TConverter>(GetConverter<TArguments>(generator)...);
    generator.AddConverter(converter);
}
}

#endif
