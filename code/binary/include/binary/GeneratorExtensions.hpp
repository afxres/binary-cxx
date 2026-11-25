#ifndef BINARY_GENERATOREXTENSIONS_HPP
#define BINARY_GENERATOREXTENSIONS_HPP

#include "binary/Converter.hpp"
#include "binary/ConverterCreator.hpp"
#include "binary/IGenerator.hpp"
#include "binary/internal/Module.hpp"

namespace binary {
template <typename T>
    requires std::same_as<T, std::remove_cv_t<T>>
std::shared_ptr<Converter<T>> GetConverter(const IGenerator& generator) {
    return ::binary::internal::GetConverter<T>(generator.GetConverter(typeid(T)));
}

template <typename T>
    requires std::same_as<T, std::remove_cv_t<T>>
Converter<T>* GetConverterRawPtr(const IGenerator& generator) {
    return ::binary::internal::GetConverterRawPtr<T>(generator.GetConverter(typeid(T)));
}

template <typename TConverter, typename... TArguments>
    requires requires(const IGenerator& generator) { ::binary::ConverterCreator<TConverter, TArguments...>::Create(generator); }
void AddConverter(IGenerator& generator) {
    std::shared_ptr<IConverter> converter = ::binary::ConverterCreator<TConverter, TArguments...>::Create(generator);
    generator.AddConverter(converter);
}
}

#endif
