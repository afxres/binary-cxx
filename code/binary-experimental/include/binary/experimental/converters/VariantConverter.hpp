#ifndef BINARY_EXPERIMENTAL_CONVERTERS_VARIANTCONVERTER_HPP
#define BINARY_EXPERIMENTAL_CONVERTERS_VARIANTCONVERTER_HPP

#include <array>
#include <utility>
#include <variant>

#include "binary/experimental/helpers/ConverterDecodeAutoMethodHelper.hpp"
#include "binary/experimental/helpers/ConverterEncodeAutoMethodHelper.hpp"
#include "binary/experimental/helpers/GetConverterHelper.hpp"
#include "binary/experimental/internal/Define.hpp"
#include "binary/internal/Exception.hpp"

namespace binary::experimental::converters {
template <typename T>
struct VariantConverter {
private:
    using EncodeFunction = void (*)(Allocator&, const T&);
    using DecodeFunction = T (*)(std::span<const std::byte>&);
    static constexpr size_t ElementCount = std::variant_size_v<T>;

    template <size_t Index>
    using ElementConverterType = typename ::binary::experimental::helpers::GetConverterHelper<std::remove_cv_t<std::variant_alternative_t<Index, T>>>::Type;

    template <size_t IsAuto, size_t Index>
    static void EncodeElement(Allocator& allocator, const T& item) {
        using ElementConverterType = ElementConverterType<Index>;
        using ElementConverterEncodeAutoMethodHelperType = ::binary::experimental::helpers::ConverterEncodeAutoMethodHelper<ElementConverterType>;
        if constexpr (IsAuto == 0) {
            ElementConverterType::Encode(allocator, std::get<Index>(item));
        } else {
            ElementConverterEncodeAutoMethodHelperType::Invoke(allocator, std::get<Index>(item));
        }
    }

    template <size_t IsAuto, size_t Index>
    static T DecodeElement(std::span<const std::byte>& span) {
        using ElementConverterType = ElementConverterType<Index>;
        using ElementConverterDecodeAutoMethodHelperType = ::binary::experimental::helpers::ConverterDecodeAutoMethodHelper<ElementConverterType>;
        if constexpr (IsAuto == 0) {
            return T{std::in_place_index<Index>, ElementConverterType::Decode(span)};
        } else {
            return T{std::in_place_index<Index>, ElementConverterDecodeAutoMethodHelperType::Invoke(span)};
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
    static void EncodeInternal(Allocator& allocator, const T& item) {
        auto header = item.index();
        if (header >= ElementCount) {
            ::binary::internal::ThrowInvalidVariantIndex(header);
        }

        ::binary::Encode(allocator, header);
        static constexpr auto table = MakeEncodeTable<IsAuto>(std::make_index_sequence<ElementCount>());
        table[header](allocator, item);
    }

    template <size_t IsAuto>
    static T DecodeInternal(std::span<const std::byte>& span) {
        auto header = ::binary::Decode(span);
        static constexpr auto table = MakeDecodeTable<IsAuto>(std::make_index_sequence<ElementCount>());
        if (header >= ElementCount) {
            ::binary::internal::ThrowInvalidVariantIndex(header);
        }
        return table[header](span);
    }

public:
    BINARY_EXPERIMENTAL_DEFINE_STATIC_LENGTH_METHOD() {
        return 0;
    }

    BINARY_EXPERIMENTAL_DEFINE_STATIC_ENCODE_METHOD(T) {
        EncodeInternal<0>(allocator, item);
    }

    BINARY_EXPERIMENTAL_DEFINE_STATIC_ENCODE_AUTO_METHOD(T) {
        EncodeInternal<1>(allocator, item);
    }

    BINARY_EXPERIMENTAL_DEFINE_STATIC_DECODE_METHOD(T) {
        std::span<const std::byte> copy = span;
        return DecodeInternal<0>(copy);
    }

    BINARY_EXPERIMENTAL_DEFINE_STATIC_DECODE_AUTO_METHOD(T) {
        return DecodeInternal<1>(span);
    }
};
}

namespace binary::experimental::helpers {
template <typename T>
    requires std::same_as<T, std::remove_cv_t<T>> &&
    requires { std::variant_size<T>::value; }
struct GetConverterHelper<T> {
    using Type = ::binary::experimental::converters::VariantConverter<T>;
};
}

#endif
