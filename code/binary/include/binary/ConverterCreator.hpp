#ifndef BINARY_CONVERTERCREATOR_HPP
#define BINARY_CONVERTERCREATOR_HPP

#include <concepts>
#include <memory>
#include <ranges>

#include "binary/Converter.hpp"
#include "binary/IGenerator.hpp"

namespace binary {
// The first template argument is the converter; the rest, when given, name the
// converters its constructor takes.
template <typename TConverter, typename... TArguments>
struct ConverterCreator;

template <typename TConverter, typename... TArguments>
    requires(sizeof...(TArguments) > 0) &&
    std::derived_from<TConverter, IConverter> &&
    std::constructible_from<TConverter, const std::shared_ptr<Converter<std::remove_cv_t<TArguments>>>&...>
struct ConverterCreator<TConverter, TArguments...> {
    static auto Create(const IGenerator& generator) {
        return std::make_shared<TConverter>(GetConverter<std::remove_cv_t<TArguments>>(generator)...);
    }
};

// Prefer a constructor that takes the generator; fall back to the default one.
template <typename TConverter>
    requires std::derived_from<TConverter, IConverter> &&
    (std::constructible_from<TConverter, const IGenerator&> || std::default_initializable<TConverter>)
struct ConverterCreator<TConverter> {
    static auto Create(const IGenerator& generator) {
        if constexpr (std::constructible_from<TConverter, const IGenerator&>) {
            return std::make_shared<TConverter>(generator);
        } else {
            return std::make_shared<TConverter>();
        }
    }
};

template <template <typename> typename TConverter, std::ranges::range TRange>
    requires std::derived_from<TConverter<TRange>, IConverter> &&
    std::constructible_from<TConverter<TRange>, const std::shared_ptr<Converter<std::ranges::range_value_t<TRange>>>&>
struct ConverterCreator<TConverter<TRange>> {
    static auto Create(const IGenerator& generator) {
        return std::make_shared<TConverter<TRange>>(GetConverter<std::ranges::range_value_t<TRange>>(generator));
    }
};

template <template <typename> typename TConverter, template <typename...> typename TValue, typename... TArguments>
    requires std::derived_from<TConverter<TValue<TArguments...>>, IConverter> &&
    std::constructible_from<TConverter<TValue<TArguments...>>, const std::shared_ptr<Converter<std::remove_cv_t<TArguments>>>&...>
struct ConverterCreator<TConverter<TValue<TArguments...>>> {
    static auto Create(const IGenerator& generator) {
        return std::make_shared<TConverter<TValue<TArguments...>>>(GetConverter<std::remove_cv_t<TArguments>>(generator)...);
    }
};
}

#endif
