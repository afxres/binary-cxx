#ifndef BINARY_EXPERIMENTAL_CONVERTERS_ARRAYCONVERTER_HPP
#define BINARY_EXPERIMENTAL_CONVERTERS_ARRAYCONVERTER_HPP

#include <array>
#include <concepts>
#include <cstddef>
#include <cstdint>
#include <type_traits>
#include <utility>

#include "binary/experimental/helpers/ConverterDecodeAutoMethodHelper.hpp"
#include "binary/experimental/helpers/ConverterEncodeAutoMethodHelper.hpp"
#include "binary/experimental/helpers/GetConverterHelper.hpp"
#include "binary/experimental/internal/Define.hpp"

namespace binary::experimental::converters {
template <typename T>
struct ArrayConverter;

// Static counterpart of `binary::converters::ArrayConverter`, same wire.
template <typename E, size_t N>
    requires std::same_as<E, std::remove_cv_t<E>>
struct ArrayConverter<std::array<E, N>> {
private:
    using T = std::array<E, N>;
    using C = typename ::binary::experimental::helpers::GetConverterHelper<E>::Type;

    template <size_t... Index>
    static T DecodeInternal(std::span<const std::byte>& span, std::index_sequence<Index...>) {
        using DecodeHelper = ::binary::experimental::helpers::ConverterDecodeAutoMethodHelper<C>;
        return T{(static_cast<void>(Index), DecodeHelper::Invoke(span))...};
    }

public:
    BINARY_EXPERIMENTAL_DEFINE_STATIC_LENGTH_METHOD() {
        constexpr size_t length = C::Length();
        if constexpr (length == 0 || N == 0) {
            return 0;
        } else {
            static_assert(N <= static_cast<size_t>(INT32_MAX) / length);
            return length * N;
        }
    }

    BINARY_EXPERIMENTAL_DEFINE_STATIC_ENCODE_METHOD(T) {
        using EncodeHelper = ::binary::experimental::helpers::ConverterEncodeAutoMethodHelper<C>;
        for (const auto& i : item) {
            EncodeHelper::Invoke(allocator, i);
        }
    }

    BINARY_EXPERIMENTAL_DEFINE_STATIC_DECODE_METHOD(T) {
        std::span<const std::byte> copy = span;
        return DecodeInternal(copy, std::make_index_sequence<N>());
    }
};
}

namespace binary::experimental::helpers {
template <typename E, size_t N>
    requires std::same_as<E, std::remove_cv_t<E>>
struct GetConverterHelper<std::array<E, N>> {
    using Type = ::binary::experimental::converters::ArrayConverter<std::array<E, N>>;
};
}

#endif
