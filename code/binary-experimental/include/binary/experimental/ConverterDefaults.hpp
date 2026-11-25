#ifndef BINARY_EXPERIMENTAL_CONVERTERDEFAULTS_HPP
#define BINARY_EXPERIMENTAL_CONVERTERDEFAULTS_HPP

#include <cstddef>
#include <span>

#include "binary/Allocator.hpp"
#include "binary/ConverterExtensions.hpp"
#include "binary/internal/AllocatorUnsafeAccessor.hpp"
#include "binary/internal/Exception.hpp"

namespace binary::experimental {
// The four entry points a converter may leave to the length rule, matching the
// virtual `binary::Converter<T>`. A converter that declares one of them hides
// the default, so `Length`/`Encode`/`Decode` are the only required members --
// declaring them here as well would make `D::Encode` resolve back to this class
// and recurse.
template <typename D>
struct ConverterDefaults {
    template <typename T>
    static void EncodeAuto(Allocator& allocator, const T& item) {
        if constexpr (D::Length() != 0) {
            D::Encode(allocator, item);
        } else {
            D::EncodeWithLengthPrefix(allocator, item);
        }
    }

    template <typename T>
    static void EncodeWithLengthPrefix(Allocator& allocator, const T& item) {
        constexpr size_t length = D::Length();
        if constexpr (length != 0) {
            ::binary::Encode(allocator, length);
            D::Encode(allocator, item);
        } else {
            using typename ::binary::internal::AllocatorUnsafeAccessor;
            size_t anchor = AllocatorUnsafeAccessor::Anchor(allocator);
            D::Encode(allocator, item);
            AllocatorUnsafeAccessor::FinishAnchor(allocator, anchor);
        }
    }

    static auto DecodeAuto(std::span<const std::byte>& span) {
        constexpr size_t length = D::Length();
        if constexpr (length != 0) {
            if (span.size() < length) {
                ::binary::internal::ThrowNotEnoughBytes();
            }
            std::span<const std::byte> copy = span;
            span = span.subspan(length);
            return D::Decode(copy);
        } else {
            return D::DecodeWithLengthPrefix(span);
        }
    }

    static auto DecodeWithLengthPrefix(std::span<const std::byte>& span) {
        return D::Decode(::binary::DecodeWithLengthPrefix(span));
    }
};
}

#endif
