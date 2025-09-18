#ifndef BINARY_EXPERIMENTAL_HELPERS_CONVERTERDECODEWITHLENGTHPREFIXMETHODHELPER_HPP
#define BINARY_EXPERIMENTAL_HELPERS_CONVERTERDECODEWITHLENGTHPREFIXMETHODHELPER_HPP

#include "binary/ConverterExtensions.hpp"
#include "binary/experimental/internal/Define.hpp"

namespace binary::experimental::helpers {
template <typename C>
struct ConverterDecodeWithLengthPrefixMethodHelper;

template <typename C>
struct ConverterDecodeWithLengthPrefixMethodHelper {
    BINARY_EXPERIMENTAL_DEFINE_STATIC_DECODE_METHOD_WITH_NAME(auto, Invoke) {
        return C::Decode(::binary::DecodeWithLengthPrefix(span));
    }
};
}

#endif
