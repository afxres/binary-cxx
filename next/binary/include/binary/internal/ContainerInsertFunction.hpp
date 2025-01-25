#ifndef BINARY_INTERNAL_CONTAINERINSERTFUNCTION_HPP
#define BINARY_INTERNAL_CONTAINERINSERTFUNCTION_HPP

#include <ranges>

namespace binary::internal {
template <typename T>
struct ContainerInsertFunction;

template <std::ranges::input_range T>
    requires requires(T& container, std::ranges::range_value_t<T>&& result) { container.emplace(result); }
struct ContainerInsertFunction<T> {
    void operator()(T& container, std::ranges::range_value_t<T>&& result) { container.emplace(result); }
};

template <std::ranges::input_range T>
    requires requires(T& container, std::ranges::range_value_t<T>&& result) { container.emplace_back(result); }
struct ContainerInsertFunction<T> {
    void operator()(T& container, std::ranges::range_value_t<T>&& result) { container.emplace_back(result); }
};
}

#endif
