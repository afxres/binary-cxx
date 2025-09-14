#ifndef BINARY_EXPERIMENTAL_INTERNAL_CONVERTER_HPP
#define BINARY_EXPERIMENTAL_INTERNAL_CONVERTER_HPP

#include <cstddef>
#include <cstdint>
#include <tuple>
#include <type_traits>

#include "binary/experimental/internal/Define.hpp"

namespace binary::experimental::internal {
template <size_t Index, typename... E>
constexpr size_t GetConverterLengthRecursively() {
    constexpr size_t length = ::binary::experimental::Converter<std::remove_cv_t<std::tuple_element_t<Index, std::tuple<E...>>>>::Length();
    static_assert(length <= INT32_MAX);
    if constexpr (Index == sizeof...(E) - 1) {
        return length;
    } else {
        constexpr size_t result = GetConverterLengthRecursively<Index + 1, E...>();
        static_assert(length + result <= INT32_MAX);
        if constexpr (length == 0 || result == 0) {
            return 0;
        } else {
            return length + result;
        }
    }
}

template <typename... E>
constexpr size_t GetConverterLength() {
    return GetConverterLengthRecursively<0, E...>();
}
}

#endif
