#ifndef BINARY_EXPERIMENTAL_INTERNAL_TUPLESIZE_HPP
#define BINARY_EXPERIMENTAL_INTERNAL_TUPLESIZE_HPP

#include <tuple>
#include <type_traits>

#include <boost/pfr.hpp>

namespace binary::experimental::internal {
template <typename T>
struct TupleSize;

template <typename T>
    requires requires { std::tuple_size<T>::value; }
struct TupleSize<T> {
    static constexpr size_t Value = std::tuple_size<T>::value;
};

template <typename T>
    requires std::is_aggregate_v<T> && requires { boost::pfr::tuple_size<T>::value; }
struct TupleSize<T> {
    static constexpr size_t Value = boost::pfr::tuple_size<T>::value;
};
}

#endif
