#ifndef BINARY_INTERNAL_TUPLEGETHELPER_HPP
#define BINARY_INTERNAL_TUPLEGETHELPER_HPP

#include <cstddef>
#include <tuple>
#include <type_traits>

namespace binary::internal {
template <size_t Index, typename T>
struct TupleGetHelper;

template <size_t Index, typename T>
    requires requires { std::tuple_size<T>::value; }
struct TupleGetHelper<Index, T> {
    static constexpr auto& Invoke(const T& item) {
        return std::get<Index>(item);
    }
};
}

#endif
