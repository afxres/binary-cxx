#ifndef BINARY_CONVERTERS_TUPLECONVERTER_HPP
#define BINARY_CONVERTERS_TUPLECONVERTER_HPP

#include <memory>
#include <tuple>

#include "binary/Converter.hpp"
#include "binary/internal/Converter.hpp"

namespace binary::converters {
template <typename T>
class TupleConverter;

template <template <typename...> typename T, typename... E>
    requires requires { std::tuple_size<T<E...>>::value; }
class TupleConverter<T<E...>> : public Converter<T<E...>> {
private:
    static constexpr size_t ElementCount = sizeof...(E);
    using ConverterTargetType = T<E...>;

    template <size_t IsAuto, size_t Index>
    void EncodeInternal(Allocator& allocator, const ConverterTargetType& item) {
        const auto& converter = std::get<Index>(this->converter);
        if constexpr (IsAuto == 0 && Index == ElementCount - 1) {
            converter->Encode(allocator, std::get<Index>(item));
        } else {
            converter->EncodeAuto(allocator, std::get<Index>(item));
        }
    }

    template <size_t IsAuto, size_t... Index>
    void EncodeInternal(Allocator& allocator, const ConverterTargetType& item, std::index_sequence<Index...>) {
        (EncodeInternal<IsAuto, Index>(allocator, item), ...);
    }

    template <size_t IsAuto, size_t Index>
    auto DecodeInternal(std::span<const std::byte>& span) {
        const auto& converter = std::get<Index>(this->converter);
        if constexpr (IsAuto == 0 && Index == ElementCount - 1) {
            return converter->Decode(span);
        } else {
            return converter->DecodeAuto(span);
        }
    }

    template <size_t IsAuto, size_t... Index>
    auto DecodeInternal(std::span<const std::byte>& span, std::index_sequence<Index...>) {
        return ConverterTargetType({DecodeInternal<IsAuto, Index>(span)...});
    }

    static size_t GetConverterLength(const std::shared_ptr<Converter<std::remove_cv_t<E>>>&... converter) {
        std::vector<std::shared_ptr<IConverter>> converters({converter...});
        auto lengths = converters | std::views::transform([](const auto& converter) { return converter->Length(); });
        return internal::GetConverterLength(lengths);
    }

    const std::tuple<std::shared_ptr<Converter<std::remove_cv_t<E>>>...> converter;

public:
    TupleConverter(const std::shared_ptr<Converter<std::remove_cv_t<E>>>&... converter)
        : Converter<ConverterTargetType>(GetConverterLength(converter...))
        , converter({converter...}) {}

    virtual void Encode(Allocator& allocator, const ConverterTargetType& item) override {
        EncodeInternal<0>(allocator, item, std::make_index_sequence<ElementCount>());
    }

    virtual void EncodeAuto(Allocator& allocator, const ConverterTargetType& item) override {
        EncodeInternal<1>(allocator, item, std::make_index_sequence<ElementCount>());
    }

    virtual ConverterTargetType Decode(const std::span<const std::byte>& span) override {
        std::span<const std::byte> copy = span;
        return DecodeInternal<0>(copy, std::make_index_sequence<ElementCount>());
    }

    virtual ConverterTargetType DecodeAuto(std::span<const std::byte>& span) override {
        return DecodeInternal<1>(span, std::make_index_sequence<ElementCount>());
    }
};
}

#endif
