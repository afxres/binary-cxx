#pragma once

#include "basic_length_calculator.hpp"

#include <tuple>

namespace mikodev::binary::converters {
template <typename... TArgs>
class tuple_converter : public abstract_converter<std::tuple<TArgs...>> {
private:
    using item_t = std::tuple<TArgs...>;

    using converter_ptr_tuple = std::tuple<abstract_converter_ptr<TArgs>...>;

    template <size_t Index, size_t Total, bool IsAuto>
    struct adapter {
        using adapter_next_t = adapter<Index + 1, Total, IsAuto>;

        static void encode(allocator& allocator, const item_t& item, const converter_ptr_tuple& converters) {
            auto& converter = *(std::get<Index>(converters));
            if constexpr (Index == Total - 1 && !IsAuto)
                converter.encode(allocator, std::get<Index>(item));
            else
                converter.encode_auto(allocator, std::get<Index>(item));
            if constexpr (Index != Total - 1)
                adapter_next_t::encode(allocator, item, converters);
        }

        static auto detach(span& span, const converter_ptr_tuple& converters) {
            auto& converter = *(std::get<Index>(converters));
            if constexpr (Index == Total - 1 && !IsAuto)
                return converter.decode(span);
            else
                return converter.decode_auto(span);
        }

        static auto decode(span& span, const converter_ptr_tuple& converters) {
            auto result = std::make_tuple(detach(span, converters));
            if constexpr (Index != Total - 1)
                return std::tuple_cat(std::move(result), adapter_next_t::decode(span, converters));
            else
                return result;
        }
    };

    using adapter_t = adapter<0, sizeof...(TArgs), false>;

    using adapter_auto_t = adapter<0, sizeof...(TArgs), true>;

    using calculator_t = basic_length_calculator<converter_ptr_tuple, sizeof...(TArgs)>;

    converter_ptr_tuple converters_;

public:
    tuple_converter(converter_ptr_tuple converters)
        : abstract_converter<item_t>::abstract_converter(calculator_t::invoke(converters)), converters_(converters) {}

    tuple_converter(abstract_converter_ptr<TArgs>... converters)
        : tuple_converter(std::make_tuple(converters...)) {}

    virtual void encode(allocator& allocator, const item_t& item) override {
        adapter_t::encode(allocator, item, converters_);
    }

    virtual void encode_auto(allocator& allocator, const item_t& item) override {
        adapter_auto_t::encode(allocator, item, converters_);
    }

    virtual item_t decode(const span& span) override {
        auto view(span);
        return adapter_t::decode(view, converters_);
    }

    virtual item_t decode_auto(span& span) override {
        return adapter_auto_t::decode(span, converters_);
    }
};
}
