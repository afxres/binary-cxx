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

template <typename T, typename R = std::invoke_result_t<decltype(Allocator::Invoke<>), const std::function<void(Allocator&)>&>>
    requires std::same_as<T, std::remove_cv_t<T>> &&
    requires { &Allocator::Invoke<R>; }
R Encode(const T& item) {
    return Allocator::Invoke<R>([&item](auto& allocator) {
        ::binary::experimental::Converter<T>::Encode(allocator, item);
    });
}

template <typename T>
    requires std::same_as<T, std::remove_cv_t<T>>
T Decode(const std::span<const std::byte>& span) {
    return ::binary::experimental::Converter<T>::Decode(span);
}
}

#endif
