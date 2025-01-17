#pragma once

#ifndef BINARY_GENERATOREXTENSIONS_HPP
#define BINARY_GENERATOREXTENSIONS_HPP

#include "Converter.hpp"
#include "ConverterExtensions.hpp"
#include "IGenerator.hpp"

namespace binary::internals {
template <typename TConverter>
struct GeneratorAddConverterFunction;

template <typename TConverter>
    requires std::derived_from<TConverter, IConverter> && std::constructible_from<TConverter>
struct GeneratorAddConverterFunction<TConverter> {
    void operator()(IGenerator& generator) {
        std::shared_ptr<IConverter> converter = std::make_shared<TConverter>();
        generator.AddConverter(converter);
    }
};

template <typename TConverter>
    requires std::derived_from<TConverter, IConverter> && std::constructible_from<TConverter, IGenerator&>
struct GeneratorAddConverterFunction<TConverter> {
    void operator()(IGenerator& generator) {
        std::shared_ptr<IConverter> converter = std::make_shared<TConverter>(generator);
        generator.AddConverter(converter);
    }
};

template <template <typename> typename TConverter, std::ranges::range TRange>
    requires std::derived_from<TConverter<TRange>, IConverter> && std::constructible_from<TConverter<TRange>, std::shared_ptr<Converter<std::ranges::range_value_t<TRange>>>>
struct GeneratorAddConverterFunction<TConverter<TRange>> {
    void operator()(IGenerator& generator) {
        std::shared_ptr<IConverter> converter = std::make_shared<TConverter<TRange>>(GetConverter<std::ranges::range_value_t<TRange>>(generator));
        generator.AddConverter(converter);
    }
};

template <template <typename> typename TConverter, template <typename...> typename TTuple, typename... TArguments>
    requires std::derived_from<TConverter<TTuple<TArguments...>>, IConverter> && std::constructible_from<TConverter<TTuple<TArguments...>>, std::shared_ptr<Converter<TArguments>>...> && requires { std::tuple_size<TTuple<TArguments...>>::value; }
struct GeneratorAddConverterFunction<TConverter<TTuple<TArguments...>>> {
    void operator()(IGenerator& generator) {
        std::shared_ptr<IConverter> converter = std::make_shared<TConverter<TTuple<TArguments...>>>(GetConverter<TArguments>(generator)...);
        generator.AddConverter(converter);
    }
};
}

namespace binary {
template <typename T>
std::shared_ptr<Converter<T>> GetConverter(const IGenerator& generator) {
    return GetConverter<T>(generator.GetConverter(typeid(T)));
}

template <typename TConverter, typename... TArguments, std::enable_if_t<std::is_same_v<std::tuple<>, std::tuple<TArguments...>> == false, bool> = true>
    requires std::derived_from<TConverter, IConverter> && std::constructible_from<TConverter, std::shared_ptr<Converter<TArguments>>...>
void AddConverter(IGenerator& generator) {
    std::shared_ptr<IConverter> converter = std::make_shared<TConverter>(GetConverter<TArguments>(generator)...);
    generator.AddConverter(converter);
}

template <typename TConverter>
    requires requires(IGenerator& generator) { internals::GeneratorAddConverterFunction<TConverter>()(generator); }
void AddConverter(IGenerator& generator) {
    internals::GeneratorAddConverterFunction<TConverter>()(generator);
}
}

#endif
