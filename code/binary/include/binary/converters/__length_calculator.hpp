#pragma once

#include "../abstract_converter.hpp"

#include <vector>

namespace mikodev::binary::converters
{
    template <typename TCvts, size_t Total, size_t Index>
    struct __length_selector
    {
        static void select(std::vector<length_t>& vector, const TCvts& converters)
        {
            vector.push_back(std::get<Index>(converters)->length());
            if constexpr (Index != Total - 1)
                __length_selector<TCvts, Total, Index + 1>::select(vector, converters);
        }
    };

    template <typename TCvts, size_t Total>
    struct __length_calculator
    {
        static length_t invoke(TCvts converters)
        {
            std::vector<length_t> vector;
            __length_selector<TCvts, Total, 0>::select(vector, converters);
            if (std::find(vector.begin(), vector.end(), 0) != vector.end())
                return 0;
            uint64_t result = 0;
            std::for_each(vector.begin(), vector.end(), [&result](length_t i) { result += static_cast<uint64_t>(i); });
            if (result > length_max)
                exceptions::throw_helper::throw_argument_out_of_range_exception();
            return static_cast<length_t>(result);
        }
    };
}
