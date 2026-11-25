#ifndef BINARY_EXPERIMENTAL_CONVERTERS_SHAREDPOINTERCONVERTER_HPP
#define BINARY_EXPERIMENTAL_CONVERTERS_SHAREDPOINTERCONVERTER_HPP

#include <memory>
#include <type_traits>

#include "binary/Allocator.hpp"
#include "binary/experimental/ConverterMethodHelper.hpp"
#include "binary/experimental/ConverterTypeHelper.hpp"
#include "binary/experimental/internal/Define.hpp"
#include "binary/internal/Exception.hpp"

namespace binary::experimental::converters {
template <typename T>
struct SharedPointerConverter;

// Static counterpart of `binary::converters::SharedPointerConverter`, same wire:
// the pointee. All six entry points are forwarded, so a pointer stays
// byte-identical to its pointee in every position.
template <typename T>
    requires std::same_as<T, std::remove_cv_t<T>>
struct SharedPointerConverter<std::shared_ptr<T>> : ConverterMethodHelper<SharedPointerConverter<std::shared_ptr<T>>> {
private:
    using P = std::shared_ptr<T>;

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

namespace binary::experimental {
template <typename T>
    requires std::same_as<T, std::remove_cv_t<T>>
struct ConverterTypeHelper<std::shared_ptr<T>> {
    using Type = ::binary::experimental::converters::SharedPointerConverter<std::shared_ptr<T>>;
};
}

#endif
