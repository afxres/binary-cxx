#ifndef BINARY_EXPERIMENTAL_CONVERTERS_TUPLECONVERTER_HPP
#define BINARY_EXPERIMENTAL_CONVERTERS_TUPLECONVERTER_HPP

#include <tuple>

#include "binary/experimental/helpers/ConverterDecodeAutoMethodHelper.hpp"
#include "binary/experimental/helpers/ConverterEncodeAutoMethodHelper.hpp"
#include "binary/experimental/internal/TupleElement.hpp"
#include "binary/experimental/internal/TupleGetHelper.hpp"
#include "binary/experimental/internal/TupleSize.hpp"

namespace binary::experimental::converters {
template <typename T>
struct TupleConverter {
    static constexpr size_t ElementCount = ::binary::experimental::internal::TupleSize<T>::Value;
    using ObjectType = T;

    template <size_t Index>
    using ElementConverterType = ::binary::experimental::Converter<std::remove_cv_t<typename ::binary::experimental::internal::TupleElement<Index, ObjectType>::Type>>;

    template <size_t IsAuto, size_t Index>
    static void EncodeInternal(Allocator& allocator, const ObjectType& item) {
        using ElementGetHelper = ::binary::experimental::internal::TupleGetHelper<Index, ObjectType>;
        using ElementConverterType = ElementConverterType<Index>;
        using ElementConverterEncodeAutoMethodHelperType = ::binary::experimental::helpers::ConverterEncodeAutoMethodHelper<ElementConverterType>;
        if constexpr (IsAuto == 0 && Index == ElementCount - 1) {
            ElementConverterType::Encode(allocator, ElementGetHelper::Invoke(item));
        } else {
            ElementConverterEncodeAutoMethodHelperType::Invoke(allocator, ElementGetHelper::Invoke(item));
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

    template <size_t Index>
    static constexpr size_t GetConverterLengthRecursively() {
        constexpr size_t length = ElementConverterType<Index>::Length();
        static_assert(length <= INT32_MAX);
        if constexpr (Index == ElementCount - 1) {
            return length;
        } else {
            constexpr size_t result = GetConverterLengthRecursively<Index + 1>();
            static_assert(length + result <= INT32_MAX);
            if constexpr (length == 0 || result == 0) {
                return 0;
            } else {
                return length + result;
            }
        }
    }

    BINARY_EXPERIMENTAL_DEFINE_STATIC_LENGTH_METHOD() {
        return GetConverterLengthRecursively<0>();
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
    requires { ::binary::experimental::internal::TupleSize<T>::Value; }
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
