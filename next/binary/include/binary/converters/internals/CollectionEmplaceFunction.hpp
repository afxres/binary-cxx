#ifndef BINARY_CONVERTERS_INTERNALS_COLLECTIONEMPLACEFUNCTION_HPP
#define BINARY_CONVERTERS_INTERNALS_COLLECTIONEMPLACEFUNCTION_HPP

#include <ranges>

namespace binary::converters::internals {
template <typename T>
struct CollectionEmplaceFunction;

template <std::ranges::input_range T>
    requires requires(T& collection, std::ranges::range_value_t<T>&& result) { collection.emplace(result); }
struct CollectionEmplaceFunction<T> {
    void operator()(T& collection, std::ranges::range_value_t<T>&& result) { collection.emplace(result); }
};

template <std::ranges::input_range T>
    requires requires(T& collection, std::ranges::range_value_t<T>&& result) { collection.emplace_back(result); }
struct CollectionEmplaceFunction<T> {
    void operator()(T& collection, std::ranges::range_value_t<T>&& result) { collection.emplace_back(result); }
};
}

#endif
