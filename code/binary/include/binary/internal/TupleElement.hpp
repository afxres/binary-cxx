#ifndef BINARY_INTERNAL_TUPLEELEMENT_HPP
#define BINARY_INTERNAL_TUPLEELEMENT_HPP

#include <cstddef>
#include <tuple>

namespace binary::internal {
template <size_t Index, typename T>
struct TupleElement;

template <size_t Index, typename T>
    requires requires { std::tuple_size<T>::value; }
struct TupleElement<Index, T> {
    using Type = typename std::tuple_element<Index, T>::type;
};
}

#endif
