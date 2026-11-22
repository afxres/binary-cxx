#ifndef BINARY_EXPERIMENTAL_CONVERTERS_OPTIONALCONVERTER_HPP
#define BINARY_EXPERIMENTAL_CONVERTERS_OPTIONALCONVERTER_HPP

#include <concepts>
#include <optional>
#include <type_traits>

#include "binary/ConverterExtensions.hpp"
#include "binary/experimental/helpers/ConverterDecodeAutoMethodHelper.hpp"
#include "binary/experimental/helpers/ConverterEncodeAutoMethodHelper.hpp"
#include "binary/experimental/helpers/GetConverterHelper.hpp"
#include "binary/experimental/internal/Define.hpp"
#include "binary/internal/Exception.hpp"

namespace binary::experimental::converters {
template <typename T>
struct OptionalConverter;

// Static counterpart of `binary::converters::OptionalConverter`. Same wire:
// length-prefixed tag (0 = empty, 1 = value) plus the value in the requested
// mode. The tag matches `VariantConverter<std::variant<std::monostate, E>>`,
// which is already pinned by the variant tests.
template <typename E>
    requires std::same_as<E, std::remove_cv_t<E>>
struct OptionalConverter<std::optional<E>> {
private:
    using T = std::optional<E>;

    using C = typename ::binary::experimental::helpers::GetConverterHelper<E>::Type;

    static constexpr size_t None = 0;
    static constexpr size_t Some = 1;

    template <bool IsAuto>
    static void EncodeInternal(Allocator& allocator, const T& item) {
        ::binary::Encode(allocator, item.has_value() ? Some : None);
        if (item.has_value()) {
            if constexpr (IsAuto) {
                ::binary::experimental::helpers::ConverterEncodeAutoMethodHelper<C>::Invoke(allocator, *item);
            } else {
                C::Encode(allocator, *item);
            }
        }
    }

    template <bool IsAuto>
    static T DecodeInternal(std::span<const std::byte>& span) {
        auto tag = ::binary::Decode(span);
        if (tag == None) {
            return {};
        }
        if (tag != Some) {
            ::binary::internal::ThrowInvalidOptionalTag(tag);
        }
        if constexpr (IsAuto) {
            return T(std::in_place, ::binary::experimental::helpers::ConverterDecodeAutoMethodHelper<C>::Invoke(span));
        } else {
            return T(std::in_place, C::Decode(span));
        }
    }

public:
    BINARY_EXPERIMENTAL_DEFINE_STATIC_LENGTH_METHOD() {
        return 0;
    }

    BINARY_EXPERIMENTAL_DEFINE_STATIC_ENCODE_METHOD(T) {
        EncodeInternal<false>(allocator, item);
    }

    BINARY_EXPERIMENTAL_DEFINE_STATIC_ENCODE_AUTO_METHOD(T) {
        EncodeInternal<true>(allocator, item);
    }

    BINARY_EXPERIMENTAL_DEFINE_STATIC_DECODE_METHOD(T) {
        return DecodeInternal<false>(span);
    }

    BINARY_EXPERIMENTAL_DEFINE_STATIC_DECODE_AUTO_METHOD(T) {
        return DecodeInternal<true>(span);
    }
};
}

namespace binary::experimental::helpers {
template <typename E>
    requires std::same_as<E, std::remove_cv_t<E>>
struct GetConverterHelper<std::optional<E>> {
    using Type = ::binary::experimental::converters::OptionalConverter<std::optional<E>>;
};
}

#endif
