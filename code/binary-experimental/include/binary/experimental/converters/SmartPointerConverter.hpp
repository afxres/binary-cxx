#ifndef BINARY_EXPERIMENTAL_CONVERTERS_SMARTPOINTERCONVERTER_HPP
#define BINARY_EXPERIMENTAL_CONVERTERS_SMARTPOINTERCONVERTER_HPP

#include <memory>
#include <type_traits>

#include "binary/Allocator.hpp"
#include "binary/experimental/ConverterDefaults.hpp"
#include "binary/experimental/helpers/GetConverterHelper.hpp"
#include "binary/experimental/internal/Define.hpp"
#include "binary/internal/Exception.hpp"

namespace binary::experimental::converters {
template <typename T>
struct SmartPointerConverter;

// Static counterpart of `binary::converters::SmartPointerConverter`, same wire:
// the pointee. All six entry points are forwarded, so a pointer stays
// byte-identical to its pointee in every position.
template <typename T, typename D>
    requires std::same_as<T, std::remove_cv_t<T>> && (!std::is_array_v<T>) && std::is_default_constructible_v<D>
struct SmartPointerConverter<std::unique_ptr<T, D>> : ConverterDefaults<SmartPointerConverter<std::unique_ptr<T, D>>> {
private:
    using P = std::unique_ptr<T, D>;

    using C = typename ::binary::experimental::helpers::GetConverterHelper<T>::Type;

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

template <typename T>
    requires std::same_as<T, std::remove_cv_t<T>>
struct SmartPointerConverter<std::shared_ptr<T>> : ConverterDefaults<SmartPointerConverter<std::shared_ptr<T>>> {
private:
    using P = std::shared_ptr<T>;

    using C = typename ::binary::experimental::helpers::GetConverterHelper<T>::Type;

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
        return std::make_shared<T>(C::Decode(span));
    }

    BINARY_EXPERIMENTAL_STATIC_DECODE_AUTO_METHOD(P) {
        return std::make_shared<T>(C::DecodeAuto(span));
    }

    BINARY_EXPERIMENTAL_STATIC_DECODE_METHOD_WITH_NAME(P, DecodeWithLengthPrefix) {
        return std::make_shared<T>(C::DecodeWithLengthPrefix(span));
    }
};
}

namespace binary::experimental::helpers {
template <typename T, typename D>
    requires std::same_as<T, std::remove_cv_t<T>> && (!std::is_array_v<T>) && std::is_default_constructible_v<D>
struct GetConverterHelper<std::unique_ptr<T, D>> {
    using Type = ::binary::experimental::converters::SmartPointerConverter<std::unique_ptr<T, D>>;
};

template <typename T>
    requires std::same_as<T, std::remove_cv_t<T>>
struct GetConverterHelper<std::shared_ptr<T>> {
    using Type = ::binary::experimental::converters::SmartPointerConverter<std::shared_ptr<T>>;
};
}

#endif
