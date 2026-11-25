#ifndef BINARY_EXPERIMENTAL_INTERNAL_TUPLESIZE_HPP
#define BINARY_EXPERIMENTAL_INTERNAL_TUPLESIZE_HPP

#include <boost/pfr.hpp>

#include "binary/internal/TupleSize.hpp"

namespace binary::internal {
// Excluded for tuple like types: `std::array` is aggregate and tuple like at
// once, so both specializations would match it and the result is ambiguous.
template <typename T>
    requires std::is_aggregate_v<T> && (!requires { std::tuple_size<T>::value; }) && requires { boost::pfr::tuple_size<T>::value; }
struct TupleSize<T> {
    static constexpr size_t Value = boost::pfr::tuple_size<T>::value;
};
}

#endif
