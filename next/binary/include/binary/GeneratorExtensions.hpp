#ifndef BINARY_GENERATOREXTENSIONS_HPP
#define BINARY_GENERATOREXTENSIONS_HPP

#include "binary/Converter.hpp"
#include "binary/ConverterExtensions.hpp"
#include "binary/IGenerator.hpp"

namespace binary::internal {
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

template <template <typename...> typename TConverter, std::ranges::range TRange, typename... TIgnore>
    requires std::derived_from<TConverter<TRange, TIgnore...>, IConverter> && std::constructible_from<TConverter<TRange, TIgnore...>, std::shared_ptr<Converter<std::ranges::range_value_t<TRange>>>>
struct GeneratorAddConverterFunction<TConverter<TRange, TIgnore...>> {
    void operator()(IGenerator& generator) {
        std::shared_ptr<IConverter> converter = std::make_shared<TConverter<TRange, TIgnore...>>(GetConverter<std::ranges::range_value_t<TRange>>(generator));
        generator.AddConverter(converter);
    }
};

template <template <typename> typename TConverter, template <typename...> typename TTuple, typename... TArguments>
    requires std::derived_from<TConverter<TTuple<TArguments...>>, IConverter> && std::constructible_from<TConverter<TTuple<TArguments...>>, std::shared_ptr<Converter<std::remove_cv_t<TArguments>>>...> && requires { std::tuple_size<TTuple<TArguments...>>::value; }
struct GeneratorAddConverterFunction<TConverter<TTuple<TArguments...>>> {
    void operator()(IGenerator& generator) {
        std::shared_ptr<IConverter> converter = std::make_shared<TConverter<TTuple<TArguments...>>>(GetConverter<std::remove_cv_t<TArguments>>(generator)...);
        generator.AddConverter(converter);
    }
};
}

namespace binary {
template <typename T>
    requires std::same_as<T, std::remove_cv_t<T>>
std::shared_ptr<Converter<T>> GetConverter(IGenerator& generator) {
    return GetConverter<T>(generator.GetConverter(typeid(Converter<T>)));
}

template <typename TConverter, typename... TArguments>
    requires std::derived_from<TConverter, IConverter> && std::constructible_from<TConverter, std::shared_ptr<Converter<TArguments>>...> && (sizeof...(TArguments) != 0)
void AddConverter(IGenerator& generator) {
    std::shared_ptr<IConverter> converter = std::make_shared<TConverter>(GetConverter<TArguments>(generator)...);
    generator.AddConverter(converter);
}

template <typename TConverter>
    requires requires(IGenerator& generator) { internal::GeneratorAddConverterFunction<TConverter>()(generator); }
void AddConverter(IGenerator& generator) {
    internal::GeneratorAddConverterFunction<TConverter>()(generator);
}
}

#endif
