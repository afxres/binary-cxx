#ifndef BINARY_EXPERIMENTAL_HELPERS_CONVERTERENCODEAUTOMETHODHELPER_HPP
#define BINARY_EXPERIMENTAL_HELPERS_CONVERTERENCODEAUTOMETHODHELPER_HPP

#include "binary/experimental/helpers/ConverterEncodeWithLengthPrefixMethodHelper.hpp"

namespace binary::experimental::helpers {
template <typename C>
struct ConverterEncodeAutoMethodHelper;

template <typename C>
struct ConverterEncodeAutoMethodHelper {
    BINARY_EXPERIMENTAL_DEFINE_STATIC_ENCODE_METHOD_WITH_NAME(auto, Invoke) {
        constexpr size_t length = C::Length();
        if constexpr (length != 0) {
            C::Encode(allocator, item);
        } else {
            ConverterEncodeWithLengthPrefixMethodHelper<C>::Invoke(allocator, item);
        }
    }
};

template <typename C>
    requires requires { &C::EncodeAuto; }
struct ConverterEncodeAutoMethodHelper<C> {
    BINARY_EXPERIMENTAL_DEFINE_STATIC_ENCODE_METHOD_WITH_NAME(auto, Invoke) {
        C::EncodeAuto(allocator, item);
    }
};
}

#endif
