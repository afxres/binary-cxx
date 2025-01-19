#pragma once

#ifndef BINARY_GENERATOREXTENSIONS_HPP
#define BINARY_GENERATOREXTENSIONS_HPP

#include "binary/Converter.hpp"
#include "binary/ConverterExtensions.hpp"
#include "binary/IGenerator.hpp"

namespace binary::internal {
template <typename T>
    requires std::is_same_v<std::add_const_t<T>, T>
class ConstantsBoxConverter : public Converter<T> {
private:
    std::shared_ptr<Converter<std::remove_const_t<T>>> converter;

public:
    ConstantsBoxConverter(std::shared_ptr<Converter<std::remove_const_t<T>>> converter)
        : Converter<T>(converter->Length())
        , converter(converter) {}

    virtual void Encode(Allocator& allocator, const T& item) override { this->converter->Encode(allocator, item); }
    virtual void EncodeAuto(Allocator& allocator, const T& item) override { this->converter->EncodeAuto(allocator, item); }
    virtual void EncodeWithLengthPrefix(Allocator& allocator, const T& item) override { this->converter->EncodeWithLengthPrefix(allocator, item); }
    virtual T Decode(const std::span<const std::byte>& span) override { return this->converter->Decode(span); }
    virtual T DecodeAuto(std::span<const std::byte>& span) override { return this->converter->DecodeAuto(span); }
    virtual T DecodeWithLengthPrefix(std::span<const std::byte>& span) override { return this->converter->DecodeWithLengthPrefix(span); }
};

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
std::shared_ptr<Converter<T>> GetConverter(IGenerator& generator) {
    auto result = generator.GetConverter(typeid(Converter<T>));
    if (result != nullptr) {
        return GetConverter<T>(result);
    }
    if constexpr (std::is_same_v<std::add_const_t<T>, T>) {
        auto remove = generator.GetConverter(typeid(Converter<std::remove_const_t<T>>));
        if (remove != nullptr) {
            auto intent = GetConverter<std::remove_const_t<T>>(remove);
            auto bridge = std::make_shared<internal::ConstantsBoxConverter<T>>(intent);
            generator.AddConverter(bridge);
            return bridge;
        }
    }
    throw std::out_of_range(std::format("converter not found, type: {}", typeid(Converter<T>).name()));
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
