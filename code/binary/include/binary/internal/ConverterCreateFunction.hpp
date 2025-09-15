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
    static auto Invoke(const IGenerator& generator) {
        return std::make_shared<TConverter>(generator);
    }
};

template <template <typename> typename TConverter, std::ranges::range TRange>
    requires std::derived_from<TConverter<TRange>, IConverter> &&
    std::constructible_from<TConverter<TRange>, const std::shared_ptr<Converter<std::ranges::range_value_t<TRange>>>&>
struct ConverterCreateFunction<TConverter<TRange>> {
    static auto Invoke(const IGenerator& generator) {
        return std::make_shared<TConverter<TRange>>(GetConverter<std::ranges::range_value_t<TRange>>(generator));
    }
};

template <template <typename> typename TConverter, template <typename...> typename TValue, typename... TArguments>
    requires std::derived_from<TConverter<TValue<TArguments...>>, IConverter> &&
    std::constructible_from<TConverter<TValue<TArguments...>>, const std::shared_ptr<Converter<std::remove_cv_t<TArguments>>>&...>
struct ConverterCreateFunction<TConverter<TValue<TArguments...>>> {
    static auto Invoke(const IGenerator& generator) {
        return std::make_shared<TConverter<TValue<TArguments...>>>(GetConverter<std::remove_cv_t<TArguments>>(generator)...);
    }
};
}

#endif
