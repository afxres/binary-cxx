#ifndef BINARY_INTERNAL_CONTAINERLENGTHFUNCTION_HPP
#define BINARY_INTERNAL_CONTAINERLENGTHFUNCTION_HPP

#include <ranges>

namespace binary::internal {
template <typename T>
struct ContainerLengthFunction;

template <std::ranges::input_range T>
struct ContainerLengthFunction<T> {
    static constexpr bool IsEnable = false;
};

template <std::ranges::input_range T>
    requires requires(const T& container) { {container.size()} -> std::convertible_to<size_t> ; }
struct ContainerLengthFunction<T> {
    static constexpr bool IsEnable = true;
    static size_t Invoke(const T& container) { return static_cast<size_t>(container.size()); }
};
}

#endif
