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
    using GenericArgument = T<E...>;
    using ElementSequence = std::make_index_sequence<sizeof...(E)>;

    template <size_t IsAuto, size_t Index>
    void EncodeInternal(Allocator& allocator, const GenericArgument& item) {
        const auto& converter = std::get<Index>(this->converter);
        if constexpr (IsAuto == 0 && Index == sizeof...(E) - 1) {
            converter->Encode(allocator, std::get<Index>(item));
        } else {
            converter->EncodeAuto(allocator, std::get<Index>(item));
        }
    }

    template <size_t IsAuto, size_t... Index>
    void EncodeInternal(Allocator& allocator, const GenericArgument& item, std::index_sequence<Index...>) {
        (EncodeInternal<IsAuto, Index>(allocator, item), ...);
    }

    template <size_t IsAuto, size_t Index>
    auto DecodeInternal(std::span<const std::byte>& span) {
        const auto& converter = std::get<Index>(this->converter);
        if constexpr (IsAuto == 0 && Index == sizeof...(E) - 1) {
            return converter->Decode(span);
        } else {
            return converter->DecodeAuto(span);
        }
    }

    template <size_t IsAuto, size_t... Index>
    auto DecodeInternal(std::span<const std::byte>& span, std::index_sequence<Index...>) {
        return GenericArgument({DecodeInternal<IsAuto, Index>(span)...});
    }

    static size_t GetConverterLength(const std::shared_ptr<Converter<std::remove_cv_t<E>>>&... converter) {
        std::vector<std::shared_ptr<IConverter>> converters({converter...});
        auto lengths = converters | std::views::transform([](const auto& converter) { return converter->Length(); });
        return internal::GetConverterLength(lengths);
    }

    const std::tuple<std::shared_ptr<Converter<std::remove_cv_t<E>>>...> converter;

public:
    TupleConverter(const std::shared_ptr<Converter<std::remove_cv_t<E>>>&... converter)
        : Converter<GenericArgument>(GetConverterLength(converter...))
        , converter({converter...}) {}

    virtual void Encode(Allocator& allocator, const GenericArgument& item) override {
        EncodeInternal<0>(allocator, item, ElementSequence());
    }

    virtual void EncodeAuto(Allocator& allocator, const GenericArgument& item) override {
        EncodeInternal<1>(allocator, item, ElementSequence());
    }

    virtual GenericArgument Decode(const std::span<const std::byte>& span) override {
        std::span<const std::byte> copy = span;
        return DecodeInternal<0>(copy, ElementSequence());
    }

    virtual GenericArgument DecodeAuto(std::span<const std::byte>& span) override {
        return DecodeInternal<1>(span, ElementSequence());
    }
};
}

#endif
