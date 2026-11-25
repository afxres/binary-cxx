#ifndef BINARY_EXPERIMENTAL_CONVERTER_HPP
#define BINARY_EXPERIMENTAL_CONVERTER_HPP

#include <concepts>
#include <functional>
#include <span>
#include <type_traits>

#include "binary/Allocator.hpp"
#include "binary/experimental/helpers/GetConverterHelper.hpp"

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
T Decode(std::span<const std::byte> span) {
    return ::binary::experimental::Converter<T>::Decode(span);
}
}

#endif
