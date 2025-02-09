#ifndef BINARY_INTERNAL_CONTAINERINSERTFUNCTION_HPP
#define BINARY_INTERNAL_CONTAINERINSERTFUNCTION_HPP

#include <ranges>

namespace binary::internal {
template <typename T>
struct ContainerInsertFunction;

template <std::ranges::input_range T>
struct ContainerInsertFunction<T> {
    static constexpr bool IsEnable = false;
};

template <std::ranges::input_range T>
    requires requires(T& container, std::ranges::range_value_t<T>&& result) { container.emplace(std::move(result)); }
struct ContainerInsertFunction<T> {
    static constexpr bool IsEnable = true;
    void operator()(T& container, std::ranges::range_value_t<T>&& result) { container.emplace(std::move(result)); }
};

template <std::ranges::input_range T>
    requires requires(T& container, std::ranges::range_value_t<T>&& result) { container.emplace_back(std::move(result)); }
struct ContainerInsertFunction<T> {
    static constexpr bool IsEnable = true;
    void operator()(T& container, std::ranges::range_value_t<T>&& result) { container.emplace_back(std::move(result)); }
};
}

#endif
