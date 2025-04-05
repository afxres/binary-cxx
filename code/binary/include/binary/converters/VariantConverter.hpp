#ifndef BINARY_CONVERTERS_VARIANTCONVERTER_HPP
#define BINARY_CONVERTERS_VARIANTCONVERTER_HPP

#include <memory>
#include <variant>

#include "binary/Converter.hpp"
#include "binary/ConverterExtensions.hpp"

namespace binary::converters {
template <typename T>
class VariantConverter;

template <template <typename...> typename T, typename... E>
    requires requires { std::variant_size<T<E...>>::value; }
class VariantConverter<T<E...>> : public Converter<T<E...>> {
private:
    using GenericArgument = T<E...>;
    using ElementSequence = std::make_index_sequence<sizeof...(E)>;

    template <size_t IsAuto, size_t Index>
    void EncodeInternal(Allocator& allocator, const GenericArgument& item) {
        if (Index == item.index()) {
            const auto& data = std::get<Index>(item);
            const auto& converter = std::get<Index>(this->converter);
            if constexpr (IsAuto == 0) {
                converter->Encode(allocator, data);
            } else {
                converter->EncodeAuto(allocator, data);
            }
        }
    }

    template <size_t IsAuto, size_t... Index>
    void EncodeInternal(Allocator& allocator, const GenericArgument& item, std::index_sequence<Index...>) {
        ::binary::Encode(allocator, item.index());
        (EncodeInternal<IsAuto, Index>(allocator, item), ...);
    }

    template <size_t IsAuto, size_t Index>
    auto DecodeInternal(std::span<const std::byte>& span, size_t index) {
        if (Index == index) {
            const auto& converter = std::get<Index>(this->converter);
            if constexpr (IsAuto == 0) {
                return GenericArgument(std::in_place_index<Index>, converter->Decode(span));
            } else {
                return GenericArgument(std::in_place_index<Index>, converter->DecodeAuto(span));
            }
        } else {
            if constexpr (Index == sizeof...(E) - 1) {
                throw std::invalid_argument("invalid variant index");
            } else {
                return DecodeInternal<IsAuto, Index + 1>(span, index);
            }
        }
    }

    template <size_t IsAuto>
    auto DecodeInternal(std::span<const std::byte>& span) {
        auto index = ::binary::Decode(span);
        return DecodeInternal<IsAuto, 0>(span, index);
    }

    const std::tuple<std::shared_ptr<Converter<std::remove_cv_t<E>>>...> converter;

public:
    VariantConverter(const std::shared_ptr<Converter<std::remove_cv_t<E>>>&... converter)
        : converter({converter...}) {}

    virtual void Encode(Allocator& allocator, const GenericArgument& item) override {
        EncodeInternal<0>(allocator, item, ElementSequence());
    }

    virtual void EncodeAuto(Allocator& allocator, const GenericArgument& item) override {
        EncodeInternal<1>(allocator, item, ElementSequence());
    }

    virtual GenericArgument Decode(const std::span<const std::byte>& span) override {
        std::span<const std::byte> copy = span;
        return DecodeInternal<0>(copy);
    }

    virtual GenericArgument DecodeAuto(std::span<const std::byte>& span) override {
        return DecodeInternal<1>(span);
    }
};
}

#endif
