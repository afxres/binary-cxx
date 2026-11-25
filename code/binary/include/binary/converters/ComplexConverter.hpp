#ifndef BINARY_CONVERTERS_COMPLEXCONVERTER_HPP
#define BINARY_CONVERTERS_COMPLEXCONVERTER_HPP

#include <cassert>
#include <complex>
#include <cstddef>
#include <memory>
#include <type_traits>

#include "binary/Converter.hpp"
#include "binary/internal/Define.hpp"
#include "binary/internal/Exception.hpp"

namespace binary::converters {
template <typename T>
class ComplexConverter;

// Real part then imaginary part, both little-endian, fixed `2 * sizeof(T)` -- the
// same bytes the C# `Complex` gets from its repeat converter. `long double` is
// excluded: it carries padding bytes and has no C# counterpart.
template <typename T>
    requires std::same_as<T, std::remove_cv_t<T>> && (std::same_as<T, float> || std::same_as<T, double>)
class ComplexConverter<std::complex<T>> : public Converter<std::complex<T>> {
private:
    using C = std::complex<T>;

    std::shared_ptr<Converter<T>> converter;

public:
    explicit ComplexConverter(const std::shared_ptr<Converter<T>>& converter)
        : Converter<C>(2 * sizeof(T))
        , converter(converter) {
        assert(converter->Length() == sizeof(T));
    }

    BINARY_OVERRIDE_ENCODE_METHOD(C) {
        this->converter->Encode(allocator, item.real());
        this->converter->Encode(allocator, item.imag());
    }

    BINARY_OVERRIDE_DECODE_METHOD(C) {
        if (span.size() < sizeof(C)) {
            ::binary::internal::ThrowNotEnoughBytes();
        }
        return C(this->converter->Decode(span.first(sizeof(T))), this->converter->Decode(span.subspan(sizeof(T)).first(sizeof(T))));
    }
};
}

#endif
