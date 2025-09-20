#ifndef BINARY_EXPERIMENTAL_HELPERS_CONVERTERENCODEWITHLENGTHPREFIXMETHODHELPER_HPP
#define BINARY_EXPERIMENTAL_HELPERS_CONVERTERENCODEWITHLENGTHPREFIXMETHODHELPER_HPP

#include "binary/ConverterExtensions.hpp"
#include "binary/internal/AllocatorUnsafeAccessor.hpp"

namespace binary::experimental::helpers {
template <typename C>
struct ConverterEncodeWithLengthPrefixMethodHelper;

template <typename C>
struct ConverterEncodeWithLengthPrefixMethodHelper {
    BINARY_EXPERIMENTAL_DEFINE_STATIC_ENCODE_METHOD_WITH_NAME(auto, Invoke) {
        constexpr size_t length = C::Length();
        if constexpr (length != 0) {
            ::binary::Encode(allocator, length);
            C::Encode(allocator, item);
        } else {
            using typename ::binary::internal::AllocatorUnsafeAccessor;
            size_t anchor = AllocatorUnsafeAccessor::Anchor(allocator);
            C::Encode(allocator, item);
            AllocatorUnsafeAccessor::FinishAnchor(allocator, anchor);
        }
    }
};

template <typename C>
    requires requires { &C::EncodeWithLengthPrefix; }
struct ConverterEncodeWithLengthPrefixMethodHelper<C> {
    BINARY_EXPERIMENTAL_DEFINE_STATIC_ENCODE_METHOD_WITH_NAME(auto, Invoke) {
        C::EncodeWithLengthPrefix(allocator, item);
    }
};
}

#endif
