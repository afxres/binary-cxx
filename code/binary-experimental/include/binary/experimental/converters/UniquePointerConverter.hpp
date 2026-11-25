#ifndef BINARY_EXPERIMENTAL_CONVERTERS_UNIQUEPOINTERCONVERTER_HPP
#define BINARY_EXPERIMENTAL_CONVERTERS_UNIQUEPOINTERCONVERTER_HPP

#include <memory>
#include <type_traits>

#include "binary/Allocator.hpp"
#include "binary/experimental/ConverterMethodHelper.hpp"
#include "binary/experimental/ConverterTypeHelper.hpp"
#include "binary/experimental/internal/Define.hpp"
#include "binary/internal/Exception.hpp"

namespace binary::experimental::converters {
template <typename T>
struct UniquePointerConverter;

// Static counterpart of `binary::converters::UniquePointerConverter`, same wire:
// the pointee. All six entry points are forwarded, so a pointer stays
// byte-identical to its pointee in every position.
template <typename T, typename D>
    requires std::same_as<T, std::remove_cv_t<T>> && (!std::is_array_v<T>) && std::is_default_constructible_v<D>
struct UniquePointerConverter<std::unique_ptr<T, D>> : ConverterMethodHelper<UniquePointerConverter<std::unique_ptr<T, D>>> {
private:
    using P = std::unique_ptr<T, D>;

    using C = typename ::binary::experimental::ConverterTypeHelper<T>::Type;

    static const T& Value(const P& item) {
        if (!item) {
            ::binary::internal::ThrowNullPointer(typeid(P));
        }
        return *item;
    }

public:
    BINARY_EXPERIMENTAL_STATIC_LENGTH_METHOD() {
        return C::Length();
    }

    BINARY_EXPERIMENTAL_STATIC_ENCODE_METHOD(P) {
        C::Encode(allocator, Value(item));
    }

    BINARY_EXPERIMENTAL_STATIC_ENCODE_AUTO_METHOD(P) {
        C::EncodeAuto(allocator, Value(item));
    }

    BINARY_EXPERIMENTAL_STATIC_ENCODE_WITH_LENGTH_PREFIX_METHOD(P) {
        C::EncodeWithLengthPrefix(allocator, Value(item));
    }

    BINARY_EXPERIMENTAL_STATIC_DECODE_METHOD(P) {
        return P(new T(C::Decode(span)));
    }

    BINARY_EXPERIMENTAL_STATIC_DECODE_AUTO_METHOD(P) {
        return P(new T(C::DecodeAuto(span)));
    }

    BINARY_EXPERIMENTAL_STATIC_DECODE_METHOD_WITH_NAME(P, DecodeWithLengthPrefix) {
        return P(new T(C::DecodeWithLengthPrefix(span)));
    }
};
}

namespace binary::experimental {
template <typename T, typename D>
    requires std::same_as<T, std::remove_cv_t<T>> && (!std::is_array_v<T>) && std::is_default_constructible_v<D>
struct ConverterTypeHelper<std::unique_ptr<T, D>> {
    using Type = ::binary::experimental::converters::UniquePointerConverter<std::unique_ptr<T, D>>;
};
}

#endif
