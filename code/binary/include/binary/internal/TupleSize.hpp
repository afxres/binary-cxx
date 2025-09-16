#ifndef BINARY_INTERNAL_TUPLESIZE_HPP
#define BINARY_INTERNAL_TUPLESIZE_HPP

#include <cstddef>
#include <tuple>
#include <type_traits>

namespace binary::internal {
template <typename T>
struct TupleSize;

template <typename T>
    requires requires { std::tuple_size<T>::value; }
struct TupleSize<T> {
    static constexpr size_t Value = std::tuple_size<T>::value;
};
}

#endif
