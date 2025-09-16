#ifndef BINARY_EXPERIMENTAL_INTERNAL_TUPLEELEMENT_HPP
#define BINARY_EXPERIMENTAL_INTERNAL_TUPLEELEMENT_HPP

#include <boost/pfr.hpp>

#include "binary/internal/TupleElement.hpp"

namespace binary::internal {
template <size_t Index, typename T>
    requires std::is_aggregate_v<T> && requires { boost::pfr::tuple_size<T>::value; }
struct TupleElement<Index, T> {
    using Type = typename boost::pfr::tuple_element<Index, T>::type;
};
}

#endif
