#ifndef BINARY_CONVERTERS_ARRAYCONVERTER_HPP
#define BINARY_CONVERTERS_ARRAYCONVERTER_HPP

#include <array>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <utility>

#include "binary/Converter.hpp"
#include "binary/internal/Define.hpp"
#include "binary/internal/Exception.hpp"

namespace binary::converters {
template <typename T>
class ArrayConverter;

// `std::array` is a fixed size container with no `emplace`, and unlike a tuple it
// has no trailing member to delimit the last element: every element stays
// self-delimited, so neither `ContainerConverter` nor `TupleConverter` serves it.
template <typename E, size_t N>
    requires std::same_as<E, std::remove_cv_t<E>>
class ArrayConverter<std::array<E, N>> : public Converter<std::array<E, N>> {
private:
    using T = std::array<E, N>;

    static size_t GetArrayLength(const std::shared_ptr<Converter<E>>& converter) {
        size_t length = converter->Length();
        if (length == 0 || N == 0) {
            return 0;
        }
        if (length > INT32_MAX || N > static_cast<size_t>(INT32_MAX) / length) {
            ::binary::internal::ThrowConverterLengthOverflow();
        }
        return length * N;
    }

    template <size_t... Index>
    T DecodeInternal(std::span<const std::byte>& span, std::index_sequence<Index...>) {
        return T{(static_cast<void>(Index), this->converter->DecodeAuto(span))...};
    }

    std::shared_ptr<Converter<E>> converter;

public:
    explicit ArrayConverter(const std::shared_ptr<Converter<E>>& converter)
        : Converter<T>(GetArrayLength(converter))
        , converter(converter) {}

    BINARY_DEFINE_OVERRIDE_ENCODE_METHOD(T) {
        for (const auto& i : item) {
            this->converter->EncodeAuto(allocator, i);
        }
    }

    BINARY_DEFINE_OVERRIDE_DECODE_METHOD(T) {
        std::span<const std::byte> copy = span;
        return DecodeInternal(copy, std::make_index_sequence<N>());
    }
};
}

#endif
