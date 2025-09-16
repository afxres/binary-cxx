#ifndef BINARY_EXPERIMENTAL_INTERNAL_TUPLEGETHELPER_HPP
#define BINARY_EXPERIMENTAL_INTERNAL_TUPLEGETHELPER_HPP

#include <boost/pfr.hpp>

#include "binary/internal/TupleGetHelper.hpp"

namespace binary::internal {
template <size_t Index, typename T>
    requires std::is_aggregate_v<T> && requires { boost::pfr::tuple_size<T>::value; }
struct TupleGetHelper<Index, T> {
    static constexpr auto& Invoke(const T& item) {
        return boost::pfr::get<Index>(item);
    }
};
}

#endif
