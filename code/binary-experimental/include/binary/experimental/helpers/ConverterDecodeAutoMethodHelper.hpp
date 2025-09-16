#ifndef BINARY_EXPERIMENTAL_HELPERS_CONVERTERDECODEAUTOMETHODHELPER_HPP
#define BINARY_EXPERIMENTAL_HELPERS_CONVERTERDECODEAUTOMETHODHELPER_HPP

#include "binary/experimental/helpers/ConverterDecodeWithLengthPrefixMethodHelper.hpp"
#include "binary/internal/Exception.hpp"

namespace binary::experimental::helpers {
template <typename C>
struct ConverterDecodeAutoMethodHelper;

template <typename C>
struct ConverterDecodeAutoMethodHelper {
    BINARY_EXPERIMENTAL_DEFINE_STATIC_DECODE_METHOD_WITH_NAME(C::ObjectType, Invoke) {
        constexpr size_t length = C::Length();
        if constexpr (length != 0) {
            if (span.size() < length) {
                ::binary::internal::ThrowNotEnoughBytes();
            }
            std::span<const std::byte> copy = span;
            span = span.subspan(length);
            return C::Decode(copy);
        } else {
            return ConverterDecodeWithLengthPrefixMethodHelper<C>::Invoke(span);
        }
    }
};

template <typename C>
    requires requires { &C::DecodeAuto; }
struct ConverterDecodeAutoMethodHelper<C> {
    BINARY_EXPERIMENTAL_DEFINE_STATIC_DECODE_METHOD_WITH_NAME(C::ObjectType, Invoke) {
        return C::DecodeAuto(span);
    }
};
}

#endif
