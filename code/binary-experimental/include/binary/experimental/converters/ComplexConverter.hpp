#ifndef BINARY_EXPERIMENTAL_CONVERTERS_COMPLEXCONVERTER_HPP
#define BINARY_EXPERIMENTAL_CONVERTERS_COMPLEXCONVERTER_HPP

#include <complex>
#include <concepts>
#include <cstddef>
#include <type_traits>

#include "binary/Allocator.hpp"
#include "binary/experimental/helpers/GetConverterHelper.hpp"
#include "binary/experimental/internal/Define.hpp"
#include "binary/internal/Exception.hpp"

namespace binary::experimental::converters {
template <typename T>
struct ComplexConverter;

// Static counterpart of `binary::converters::ComplexConverter`, same wire.
template <typename T>
    requires std::same_as<T, std::remove_cv_t<T>> && (std::same_as<T, float> || std::same_as<T, double>)
struct ComplexConverter<std::complex<T>> {
private:
    using C = std::complex<T>;
    using L = typename ::binary::experimental::helpers::GetConverterHelper<T>::Type;

public:
    BINARY_EXPERIMENTAL_STATIC_LENGTH_METHOD() {
        static_assert(L::Length() == sizeof(T));
        return 2 * sizeof(T);
    }

    BINARY_EXPERIMENTAL_STATIC_ENCODE_METHOD(C) {
        L::Encode(allocator, item.real());
        L::Encode(allocator, item.imag());
    }

    BINARY_EXPERIMENTAL_STATIC_DECODE_METHOD(C) {
        if (span.size() < sizeof(C)) {
            ::binary::internal::ThrowNotEnoughBytes();
        }
        return C(L::Decode(span.first(sizeof(T))), L::Decode(span.subspan(sizeof(T)).first(sizeof(T))));
    }
};
}

namespace binary::experimental::helpers {
template <typename T>
    requires std::same_as<T, std::remove_cv_t<T>> && (std::same_as<T, float> || std::same_as<T, double>)
struct GetConverterHelper<std::complex<T>> {
    using Type = ::binary::experimental::converters::ComplexConverter<std::complex<T>>;
};
}

#endif
