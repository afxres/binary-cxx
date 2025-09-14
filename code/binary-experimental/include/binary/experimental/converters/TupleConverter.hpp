#ifndef BINARY_EXPERIMENTAL_CONVERTERS_TUPLECONVERTER_HPP
#define BINARY_EXPERIMENTAL_CONVERTERS_TUPLECONVERTER_HPP

#include <tuple>

#include "binary/experimental/helpers/ConverterDecodeAutoMethodHelper.hpp"
#include "binary/experimental/helpers/ConverterEncodeAutoMethodHelper.hpp"
#include "binary/experimental/internal/Converter.hpp"

namespace binary::experimental::converters {
template <typename T>
struct TupleConverter;

template <template <typename...> typename T, typename... E>
    requires requires { std::tuple_size<T<E...>>::value; }
struct TupleConverter<T<E...>> {
    static constexpr size_t ElementCount = sizeof...(E);
    using ObjectType = T<E...>;

    template <size_t Index>
    using ElementConverterType = ::binary::experimental::Converter<std::remove_cv_t<std::tuple_element_t<Index, ObjectType>>>;

    template <size_t IsAuto, size_t Index>
    static void EncodeInternal(Allocator& allocator, const ObjectType& item) {
        using ElementConverterType = ElementConverterType<Index>;
        using ElementConverterEncodeAutoMethodHelperType = ::binary::experimental::helpers::ConverterEncodeAutoMethodHelper<ElementConverterType>;
        if constexpr (IsAuto == 0 && Index == ElementCount - 1) {
            ElementConverterType::Encode(allocator, std::get<Index>(item));
        } else {
            ElementConverterEncodeAutoMethodHelperType::Invoke(allocator, std::get<Index>(item));
        }
    }

    template <size_t IsAuto, size_t... Index>
    static void EncodeInternal(Allocator& allocator, const ObjectType& item, std::index_sequence<Index...>) {
        (EncodeInternal<IsAuto, Index>(allocator, item), ...);
    }

    template <size_t IsAuto, size_t Index>
    static auto DecodeInternal(std::span<const std::byte>& span) {
        using ElementConverterType = ElementConverterType<Index>;
        using ElementConverterDecodeAutoMethodHelperType = ::binary::experimental::helpers::ConverterDecodeAutoMethodHelper<ElementConverterType>;
        if constexpr (IsAuto == 0 && Index == ElementCount - 1) {
            return ElementConverterType::Decode(span);
        } else {
            return ElementConverterDecodeAutoMethodHelperType::Invoke(span);
        }
    }

    template <size_t IsAuto, size_t... Index>
    static auto DecodeInternal(std::span<const std::byte>& span, std::index_sequence<Index...>) {
        return ObjectType({DecodeInternal<IsAuto, Index>(span)...});
    }

    BINARY_EXPERIMENTAL_DEFINE_STATIC_LENGTH_METHOD() {
        return ::binary::experimental::internal::GetConverterLength<E...>();
    }

    BINARY_EXPERIMENTAL_DEFINE_STATIC_ENCODE_METHOD(ObjectType) {
        EncodeInternal<0>(allocator, item, std::make_index_sequence<ElementCount>());
    }

    BINARY_EXPERIMENTAL_DEFINE_STATIC_ENCODE_AUTO_METHOD(ObjectType) {
        EncodeInternal<1>(allocator, item, std::make_index_sequence<ElementCount>());
    }

    BINARY_EXPERIMENTAL_DEFINE_STATIC_DECODE_METHOD(ObjectType) {
        std::span<const std::byte> copy = span;
        return DecodeInternal<0>(copy, std::make_index_sequence<ElementCount>());
    }

    BINARY_EXPERIMENTAL_DEFINE_STATIC_DECODE_AUTO_METHOD(ObjectType) {
        return DecodeInternal<1>(span, std::make_index_sequence<ElementCount>());
    }
};
}

namespace binary::experimental {
template <typename T>
    requires std::same_as<T, std::remove_cv_t<T>> &&
    requires { std::tuple_size<T>::value; }
struct Converter<T> {
    using ObjectType = T;
    using ActualConverterType = ::binary::experimental::converters::TupleConverter<T>;
    BINARY_EXPERIMENTAL_FORWARD_STATIC_LENGTH_METHOD();
    BINARY_EXPERIMENTAL_FORWARD_STATIC_ENCODE_METHOD();
    BINARY_EXPERIMENTAL_FORWARD_STATIC_ENCODE_AUTO_METHOD();
    BINARY_EXPERIMENTAL_FORWARD_STATIC_DECODE_METHOD();
    BINARY_EXPERIMENTAL_FORWARD_STATIC_DECODE_AUTO_METHOD();
};
}

#endif
