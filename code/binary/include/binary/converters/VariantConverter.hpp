#ifndef BINARY_CONVERTERS_VARIANTCONVERTER_HPP
#define BINARY_CONVERTERS_VARIANTCONVERTER_HPP

#include <array>
#include <memory>
#include <tuple>
#include <variant>

#include "binary/Converter.hpp"
#include "binary/ConverterExtensions.hpp"
#include "binary/internal/Define.hpp"
#include "binary/internal/Exception.hpp"

namespace binary::converters {
template <typename T>
class VariantConverter;

template <template <typename...> typename V, typename... E>
    requires requires { std::variant_size<V<E...>>::value; }
class VariantConverter<V<E...>> : public Converter<V<E...>> {
private:
    using T = V<E...>;
    using EncodeFunction = void (VariantConverter::*)(Allocator&, const T&);
    using DecodeFunction = T (VariantConverter::*)(std::span<const std::byte>&);

    static constexpr size_t ElementCount = sizeof...(E);

    template <size_t IsAuto, size_t Index>
    void EncodeElement(Allocator& allocator, const T& item) {
        const auto& element = std::get<Index>(this->converter);
        if constexpr (IsAuto == 0) {
            element->Encode(allocator, std::get<Index>(item));
        } else {
            element->EncodeAuto(allocator, std::get<Index>(item));
        }
    }

    template <size_t IsAuto, size_t Index>
    T DecodeElement(std::span<const std::byte>& span) {
        const auto& element = std::get<Index>(this->converter);
        if constexpr (IsAuto == 0) {
            return T(std::in_place_index<Index>, element->Decode(span));
        } else {
            return T(std::in_place_index<Index>, element->DecodeAuto(span));
        }
    }

    template <size_t IsAuto, size_t... Index>
    static constexpr std::array<EncodeFunction, sizeof...(Index)> MakeEncodeTable(std::index_sequence<Index...>) {
        return std::array<EncodeFunction, sizeof...(Index)>{&VariantConverter::template EncodeElement<IsAuto, Index>...};
    }

    template <size_t IsAuto, size_t... Index>
    static constexpr std::array<DecodeFunction, sizeof...(Index)> MakeDecodeTable(std::index_sequence<Index...>) {
        return std::array<DecodeFunction, sizeof...(Index)>{&VariantConverter::template DecodeElement<IsAuto, Index>...};
    }

    template <size_t IsAuto>
    void EncodeInternal(Allocator& allocator, const T& item) {
        auto header = item.index();
        if (header >= ElementCount) {
            ::binary::internal::ThrowInvalidVariantIndex(header);
        }

        ::binary::Encode(allocator, header);
        static constexpr auto table = MakeEncodeTable<IsAuto>(std::make_index_sequence<ElementCount>());
        (this->*table[header])(allocator, item);
    }

    template <size_t IsAuto>
    T DecodeInternal(std::span<const std::byte>& span) {
        auto header = ::binary::Decode(span);
        if (header >= ElementCount) {
            ::binary::internal::ThrowInvalidVariantIndex(header);
        }

        static constexpr auto table = MakeDecodeTable<IsAuto>(std::make_index_sequence<ElementCount>());
        return (this->*table[header])(span);
    }

    std::tuple<std::shared_ptr<Converter<std::remove_cv_t<E>>>...> converter;

public:
    explicit VariantConverter(const std::shared_ptr<Converter<std::remove_cv_t<E>>>&... converter)
        : converter({converter...}) {}

    BINARY_DEFINE_OVERRIDE_ENCODE_METHOD(T) {
        EncodeInternal<0>(allocator, item);
    }

    BINARY_DEFINE_OVERRIDE_ENCODE_AUTO_METHOD(T) {
        EncodeInternal<1>(allocator, item);
    }

    BINARY_DEFINE_OVERRIDE_DECODE_METHOD(T) {
        std::span<const std::byte> copy = span;
        return DecodeInternal<0>(copy);
    }

    BINARY_DEFINE_OVERRIDE_DECODE_AUTO_METHOD(T) {
        return DecodeInternal<1>(span);
    }
};
}

#endif
