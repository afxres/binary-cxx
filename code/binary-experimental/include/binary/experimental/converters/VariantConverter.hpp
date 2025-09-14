#ifndef BINARY_EXPERIMENTAL_CONVERTERS_VARIANTCONVERTER_HPP
#define BINARY_EXPERIMENTAL_CONVERTERS_VARIANTCONVERTER_HPP

#include <variant>

#include "binary/experimental/helpers/ConverterDecodeAutoMethodHelper.hpp"
#include "binary/experimental/helpers/ConverterEncodeAutoMethodHelper.hpp"
#include "binary/experimental/internal/Define.hpp"
#include "binary/internal/Exception.hpp"

namespace binary::experimental::converters {
template <typename T>
struct VariantConverter {
    static constexpr size_t ElementCount = std::variant_size_v<T>;

    template <size_t Index>
    using ElementConverterType = ::binary::experimental::Converter<std::remove_cv_t<std::variant_alternative_t<Index, T>>>;

    template <size_t IsAuto, size_t Index>
    static void EncodeInternal(Allocator& allocator, const T& item) {
        if (Index == item.index()) {
            using ElementConverterType = ElementConverterType<Index>;
            using ElementConverterEncodeAutoMethodHelperType = ::binary::experimental::helpers::ConverterEncodeAutoMethodHelper<ElementConverterType>;
            if constexpr (IsAuto == 0) {
                ElementConverterType::Encode(allocator, std::get<Index>(item));
            } else {
                ElementConverterEncodeAutoMethodHelperType::Invoke(allocator, std::get<Index>(item));
            }
        } else {
            if constexpr (Index == ElementCount - 1) {
                internal::ThrowInvalidVariantIndex(item.index());
            } else {
                EncodeInternal<IsAuto, Index + 1>(allocator, item);
            }
        }
    }

    template <size_t IsAuto>
    static void EncodeInternal(Allocator& allocator, const T& item) {
        ::binary::Encode(allocator, item.index());
        EncodeInternal<IsAuto, 0>(allocator, item);
    }

    template <size_t IsAuto, size_t Index>
    static auto DecodeInternal(std::span<const std::byte>& span, size_t index) {
        if (Index == index) {
            using ElementConverterType = ElementConverterType<Index>;
            using ElementConverterDecodeAutoMethodHelperType = ::binary::experimental::helpers::ConverterDecodeAutoMethodHelper<ElementConverterType>;
            if constexpr (IsAuto == 0) {
                return T{std::in_place_index<Index>, ElementConverterType::Decode(span)};
            } else {
                return T{std::in_place_index<Index>, ElementConverterDecodeAutoMethodHelperType::Invoke(span)};
            }
        } else {
            if constexpr (Index == ElementCount - 1) {
                internal::ThrowInvalidVariantIndex(index);
            } else {
                return DecodeInternal<IsAuto, Index + 1>(span, index);
            }
        }
    }

    template <size_t IsAuto>
    static auto DecodeInternal(std::span<const std::byte>& span) {
        auto index = ::binary::Decode(span);
        return DecodeInternal<IsAuto, 0>(span, index);
    }

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

namespace binary::experimental {
template <typename T>
    requires std::same_as<T, std::remove_cv_t<T>> &&
    requires { std::variant_size<T>::value; }
struct Converter<T> {
    using ObjectType = T;
    using ActualConverterType = ::binary::experimental::converters::VariantConverter<T>;
    BINARY_EXPERIMENTAL_FORWARD_STATIC_LENGTH_METHOD();
    BINARY_EXPERIMENTAL_FORWARD_STATIC_ENCODE_METHOD();
    BINARY_EXPERIMENTAL_FORWARD_STATIC_ENCODE_AUTO_METHOD();
    BINARY_EXPERIMENTAL_FORWARD_STATIC_DECODE_METHOD();
    BINARY_EXPERIMENTAL_FORWARD_STATIC_DECODE_AUTO_METHOD();
};
}

#endif
