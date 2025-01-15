#ifndef BINARY_CONVERTERS_INTERNALS_COLLECTIONEMPLACEFUNCTION_HPP
#define BINARY_CONVERTERS_INTERNALS_COLLECTIONEMPLACEFUNCTION_HPP

#include <ranges>

namespace binary::converters::internals {
template <typename T>
concept CollectionWithEmplace = std::ranges::input_range<T> && requires(T& collection, std::ranges::range_value_t<T>&& result) { collection.emplace(result); };

template <typename T>
concept CollectionWithEmplaceBack = std::ranges::input_range<T> && requires(T& collection, std::ranges::range_value_t<T>&& result) { collection.emplace_back(result); };

template <typename T>
struct CollectionEmplaceFunction;

template <CollectionWithEmplace T>
struct CollectionEmplaceFunction<T> {
    void operator()(T& collection, std::ranges::range_value_t<T>&& result) { collection.emplace(result); }
};

template <CollectionWithEmplaceBack T>
struct CollectionEmplaceFunction<T> {
    void operator()(T& collection, std::ranges::range_value_t<T>&& result) { collection.emplace_back(result); }
};
}

#endif
