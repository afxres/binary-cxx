#ifndef BINARY_INTERNAL_CONTAINERRESIZEFUNCTION_HPP
#define BINARY_INTERNAL_CONTAINERRESIZEFUNCTION_HPP

#include <ranges>

namespace binary::internal {
template <typename T>
struct ContainerResizeFunction;

template <std::ranges::input_range T>
struct ContainerResizeFunction<T> {
    static constexpr bool IsEnable = false;
};

template <std::ranges::input_range T>
    requires requires(T& container, size_t size) { container.reserve(size); }
struct ContainerResizeFunction<T> {
    static constexpr bool IsEnable = true;
    static void Invoke(T& container, size_t size) { container.reserve(size); }
};
}

#endif
