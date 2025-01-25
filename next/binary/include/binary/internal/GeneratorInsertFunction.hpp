#ifndef BINARY_INTERNAL_GENERATORINSERTFUNCTION_HPP
#define BINARY_INTERNAL_GENERATORINSERTFUNCTION_HPP

#include <concepts>
#include <memory>
#include <ranges>

#include "binary/Converter.hpp"
#include "binary/IGenerator.hpp"

namespace binary::internal {
template <typename TConverter>
struct GeneratorInsertFunction;

template <typename TConverter>
    requires std::derived_from<TConverter, IConverter> && std::constructible_from<TConverter>
struct GeneratorInsertFunction<TConverter> {
    void operator()(IGenerator& generator) {
        std::shared_ptr<IConverter> converter = std::make_shared<TConverter>();
        generator.AddConverter(converter);
    }
};

template <typename TConverter>
    requires std::derived_from<TConverter, IConverter> && std::constructible_from<TConverter, IGenerator&>
struct GeneratorInsertFunction<TConverter> {
    void operator()(IGenerator& generator) {
        std::shared_ptr<IConverter> converter = std::make_shared<TConverter>(generator);
        generator.AddConverter(converter);
    }
};

template <template <typename...> typename TConverter, std::ranges::range TRange, typename... TIgnore>
    requires std::derived_from<TConverter<TRange, TIgnore...>, IConverter> && std::constructible_from<TConverter<TRange, TIgnore...>, std::shared_ptr<Converter<std::ranges::range_value_t<TRange>>>>
struct GeneratorInsertFunction<TConverter<TRange, TIgnore...>> {
    void operator()(IGenerator& generator) {
        std::shared_ptr<IConverter> converter = std::make_shared<TConverter<TRange, TIgnore...>>(GetConverter<std::ranges::range_value_t<TRange>>(generator));
        generator.AddConverter(converter);
    }
};

template <template <typename> typename TConverter, template <typename...> typename TTuple, typename... TArguments>
    requires std::derived_from<TConverter<TTuple<TArguments...>>, IConverter> && std::constructible_from<TConverter<TTuple<TArguments...>>, std::shared_ptr<Converter<std::remove_cv_t<TArguments>>>...> && requires { std::tuple_size<TTuple<TArguments...>>::value; }
struct GeneratorInsertFunction<TConverter<TTuple<TArguments...>>> {
    void operator()(IGenerator& generator) {
        std::shared_ptr<IConverter> converter = std::make_shared<TConverter<TTuple<TArguments...>>>(GetConverter<std::remove_cv_t<TArguments>>(generator)...);
        generator.AddConverter(converter);
    }
};
}

#endif
