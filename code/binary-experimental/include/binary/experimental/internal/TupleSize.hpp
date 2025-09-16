#ifndef BINARY_EXPERIMENTAL_INTERNAL_TUPLESIZE_HPP
#define BINARY_EXPERIMENTAL_INTERNAL_TUPLESIZE_HPP

#include <boost/pfr.hpp>

#include "binary/internal/TupleSize.hpp"

namespace binary::internal {
template <typename T>
    requires std::is_aggregate_v<T> && requires { boost::pfr::tuple_size<T>::value; }
struct TupleSize<T> {
    static constexpr size_t Value = boost::pfr::tuple_size<T>::value;
};
}

#endif
