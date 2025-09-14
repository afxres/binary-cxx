#ifndef BINARY_EXPERIMENTAL_INTERNAL_TUPLEGETHELPER_HPP
#define BINARY_EXPERIMENTAL_INTERNAL_TUPLEGETHELPER_HPP

#include <cstddef>
#include <tuple>
#include <type_traits>

#include <boost/pfr.hpp>

namespace binary::experimental::internal {
template <size_t Index, typename T>
struct TupleGetHelper;

template <size_t Index, typename T>
    requires requires { std::tuple_size<T>::value; }
struct TupleGetHelper<Index, T> {
    static constexpr auto& Invoke(const T& item) {
        return std::get<Index>(item);
    }
};

template <size_t Index, typename T>
    requires std::is_aggregate_v<T> && requires { boost::pfr::tuple_size<T>::value; }
struct TupleGetHelper<Index, T> {
    static constexpr auto& Invoke(const T& item) {
        return boost::pfr::get<Index>(item);
    }
};
}

#endif
