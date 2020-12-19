#pragma once

#include "../abstract_converter.hpp"

#include <algorithm>
#include <vector>

namespace mikodev::binary::converters
{
    template <typename Converters, size_t Total>
    struct basic_length_calculator
    {
        template <size_t Index>
        struct selector
        {
            static void select(std::vector<length_t>& vector, const Converters& converters)
            {
                vector.push_back(std::get<Index>(converters)->length());
                if constexpr (Index != Total - 1)
                    selector<Index + 1>::select(vector, converters);
            }
        };

        static length_t invoke(Converters converters)
        {
            std::vector<length_t> vector;
            selector<0>::select(vector, converters);
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
