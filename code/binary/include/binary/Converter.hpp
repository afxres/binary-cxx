#ifndef BINARY_CONVERTER_HPP
#define BINARY_CONVERTER_HPP

#include <cstddef>
#include <span>

#include "binary/Allocator.hpp"
#include "binary/ConverterExtensions.hpp"
#include "binary/IConverter.hpp"
#include "binary/internal/AllocatorUnsafeAccessor.hpp"
#include "binary/internal/Exception.hpp"

namespace binary {
template <typename T>
    requires std::same_as<T, std::remove_cv_t<T>>
class Converter : public IConverter {
public:
    Converter()
        : IConverter(typeid(T)) {}

    Converter(size_t length)
        : IConverter(typeid(T), length) {}

    virtual void Encode(Allocator& allocator, const T& item) = 0;

    virtual void EncodeAuto(Allocator& allocator, const T& item) {
        size_t length = Length();
        if (length != 0) {
            Encode(allocator, item);
        } else {
            EncodeWithLengthPrefix(allocator, item);
        }
    }

    virtual void EncodeWithLengthPrefix(Allocator& allocator, const T& item) {
        using typename ::binary::internal::AllocatorUnsafeAccessor;
        size_t anchor = AllocatorUnsafeAccessor::Anchor(allocator);
        Encode(allocator, item);
        AllocatorUnsafeAccessor::FinishAnchor(allocator, anchor);
    }

    virtual T Decode(const std::span<const std::byte>& span) = 0;

    virtual T DecodeAuto(std::span<const std::byte>& span) {
        size_t length = Length();
        if (length != 0) {
            if (span.size() < length) {
                ::binary::internal::ThrowNotEnoughBytes();
            }
            std::span<const std::byte> copy = span;
            span = span.subspan(length);
            return Decode(copy);
        } else {
            return DecodeWithLengthPrefix(span);
        }
    }

    virtual T DecodeWithLengthPrefix(std::span<const std::byte>& span) {
        return Decode(::binary::DecodeWithLengthPrefix(span));
    }
};
}

#endif
