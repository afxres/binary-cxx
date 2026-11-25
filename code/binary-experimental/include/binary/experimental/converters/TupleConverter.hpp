#ifndef BINARY_EXPERIMENTAL_CONVERTERS_TUPLECONVERTER_HPP
#define BINARY_EXPERIMENTAL_CONVERTERS_TUPLECONVERTER_HPP

#include <ranges>

#include "binary/experimental/ConverterMethodHelper.hpp"
#include "binary/experimental/ConverterTypeHelper.hpp"
#include "binary/experimental/internal/Define.hpp"
#include "binary/experimental/internal/TupleElement.hpp"
#include "binary/experimental/internal/TupleGetHelper.hpp"
#include "binary/experimental/internal/TupleSize.hpp"

namespace binary::experimental::converters {
// A range is not a tuple: it is written by its own converter family, with a
// boundary per element, so the positional treatment of it would disagree.
template <typename T>
    requires requires { ::binary::internal::TupleSize<T>::Value; } && (!std::ranges::range<T>)
struct TupleConverter : ConverterMethodHelper<TupleConverter<T>> {
private:
    static constexpr size_t ElementCount = ::binary::internal::TupleSize<T>::Value;
    static_assert(ElementCount > 0, "zero-member tuples are not supported");

    template <size_t Index>
    using ElementConverterType = typename ::binary::experimental::ConverterTypeHelper<std::remove_cv_t<typename ::binary::internal::TupleElement<Index, T>::Type>>::Type;

    template <size_t IsAuto, size_t Index>
    static void EncodeInternal(Allocator& allocator, const T& item) {
        using ElementGetHelper = ::binary::internal::TupleGetHelper<Index, T>;
        using ElementConverterType = ElementConverterType<Index>;
        if constexpr (IsAuto == 0 && Index == ElementCount - 1) {
            ElementConverterType::Encode(allocator, ElementGetHelper::Invoke(item));
        } else {
            ElementConverterType::EncodeAuto(allocator, ElementGetHelper::Invoke(item));
        }
    }

    template <size_t IsAuto, size_t... Index>
    static void EncodeInternal(Allocator& allocator, const T& item, std::index_sequence<Index...>) {
        (EncodeInternal<IsAuto, Index>(allocator, item), ...);
    }

    template <size_t IsAuto, size_t Index>
    static auto DecodeInternal(std::span<const std::byte>& span) {
        using ElementConverterType = ElementConverterType<Index>;
        if constexpr (IsAuto == 0 && Index == ElementCount - 1) {
            return ElementConverterType::Decode(span);
        } else {
            return ElementConverterType::DecodeAuto(span);
        }
    }

    template <size_t IsAuto, size_t... Index>
    static auto DecodeInternal(std::span<const std::byte>& span, std::index_sequence<Index...>) {
        return T{DecodeInternal<IsAuto, Index>(span)...};
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

public:
    BINARY_EXPERIMENTAL_STATIC_LENGTH_METHOD() {
        return GetConverterLengthRecursively<0>();
    }

    BINARY_EXPERIMENTAL_STATIC_ENCODE_METHOD(T) {
        EncodeInternal<0>(allocator, item, std::make_index_sequence<ElementCount>());
    }

    BINARY_EXPERIMENTAL_STATIC_ENCODE_AUTO_METHOD(T) {
        EncodeInternal<1>(allocator, item, std::make_index_sequence<ElementCount>());
    }

    BINARY_EXPERIMENTAL_STATIC_DECODE_METHOD(T) {
        std::span<const std::byte> copy = span;
        return DecodeInternal<0>(copy, std::make_index_sequence<ElementCount>());
    }

    BINARY_EXPERIMENTAL_STATIC_DECODE_AUTO_METHOD(T) {
        return DecodeInternal<1>(span, std::make_index_sequence<ElementCount>());
    }
};
}

namespace binary::experimental {
template <typename T>
    requires std::same_as<T, std::remove_cv_t<T>> &&
    requires { ::binary::internal::TupleSize<T>::Value; } &&
    (!std::ranges::range<T>) &&
    (!requires { GetNamedObjectSchema(static_cast<std::remove_cv_t<T>*>(nullptr)); }) &&
    (!requires { GetTupleObjectSchema(static_cast<std::remove_cv_t<T>*>(nullptr)); })
struct ConverterTypeHelper<T> {
    using Type = ::binary::experimental::converters::TupleConverter<T>;
};
}

#endif
