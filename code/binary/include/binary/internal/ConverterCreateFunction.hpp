#ifndef BINARY_INTERNAL_CONVERTERCREATEFUNCTION_HPP
#define BINARY_INTERNAL_CONVERTERCREATEFUNCTION_HPP

#include <concepts>
#include <memory>
#include <ranges>

#include "binary/Converter.hpp"
#include "binary/IGenerator.hpp"

namespace binary::internal {
template <typename TConverter>
struct ConverterCreateFunction;

template <typename TConverter>
    requires std::derived_from<TConverter, IConverter> && std::constructible_from<TConverter, const IGenerator&>
struct ConverterCreateFunction<TConverter> {
    auto operator()(const IGenerator& generator) {
        return std::make_shared<TConverter>(generator);
    }
};

template <template <typename> typename TConverter, std::ranges::range TRange>
    requires std::derived_from<TConverter<TRange>, IConverter> &&
    std::constructible_from<TConverter<TRange>, const std::shared_ptr<Converter<std::ranges::range_value_t<TRange>>>&>
struct ConverterCreateFunction<TConverter<TRange>> {
    auto operator()(const IGenerator& generator) {
        return std::make_shared<TConverter<TRange>>(GetConverter<std::ranges::range_value_t<TRange>>(generator));
    }
};

template <template <typename> typename TConverter, template <typename...> typename TTuple, typename... TArguments>
    requires std::derived_from<TConverter<TTuple<TArguments...>>, IConverter> &&
    std::constructible_from<TConverter<TTuple<TArguments...>>, const std::shared_ptr<Converter<std::remove_cv_t<TArguments>>>&...> &&
    requires { std::tuple_size<TTuple<TArguments...>>::value; }
struct ConverterCreateFunction<TConverter<TTuple<TArguments...>>> {
    auto operator()(const IGenerator& generator) {
        return std::make_shared<TConverter<TTuple<TArguments...>>>(GetConverter<std::remove_cv_t<TArguments>>(generator)...);
    }
};

template <template <typename> typename TConverter, template <typename...> typename TVariant, typename... TArguments>
    requires std::derived_from<TConverter<TVariant<TArguments...>>, IConverter> &&
    std::constructible_from<TConverter<TVariant<TArguments...>>, const std::shared_ptr<Converter<std::remove_cv_t<TArguments>>>&...> &&
    requires { std::variant_size<TVariant<TArguments...>>::value; }
struct ConverterCreateFunction<TConverter<TVariant<TArguments...>>> {
    auto operator()(const IGenerator& generator) {
        return std::make_shared<TConverter<TVariant<TArguments...>>>(GetConverter<std::remove_cv_t<TArguments>>(generator)...);
    }
};
}

#endif
