#ifndef BINARY_CONVERTERS_INTERNALS_COLLECTIONRESERVEFUNCTION_HPP
#define BINARY_CONVERTERS_INTERNALS_COLLECTIONRESERVEFUNCTION_HPP

#include <ranges>

namespace binary::converters::internals {
template <typename T>
struct CollectionReserveFunction;

template <std::ranges::input_range T>
struct CollectionReserveFunction<T> {
    static constexpr bool IsEnable = false;
};

template <std::ranges::input_range T>
    requires requires(T& collection, size_t size) { collection.reserve(size); }
struct CollectionReserveFunction<T> {
    static constexpr bool IsEnable = true;
    void operator()(T& collection, size_t size) { collection.reserve(size); }
};
}

#endif
