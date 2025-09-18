#ifndef BINARY_EXPERIMENTAL_CONVERTER_HPP
#define BINARY_EXPERIMENTAL_CONVERTER_HPP

#include "binary/experimental/converters/ContainerConverter.hpp"
#include "binary/experimental/converters/LittleEndianConverter.hpp"
#include "binary/experimental/converters/LittleEndianStringConverter.hpp"
#include "binary/experimental/converters/TupleConverter.hpp"
#include "binary/experimental/converters/VariantConverter.hpp"

namespace binary::experimental {
template <typename T>
    requires std::same_as<T, std::remove_cv_t<T>>
using Converter = typename ::binary::experimental::helpers::GetConverterHelper<T>::Type;

template <typename T>
    requires std::same_as<T, std::remove_cv_t<T>>
std::vector<std::byte> Encode(const T& item) {
    Allocator allocator;
    ::binary::experimental::Converter<T>::Encode(allocator, item);
    auto span = allocator.AsSpan();
    return std::vector(span.begin(), span.end());
}

template <typename T>
    requires std::same_as<T, std::remove_cv_t<T>>
T Decode(const std::span<const std::byte>& span) {
    return ::binary::experimental::Converter<T>::Decode(span);
}
}

#endif
