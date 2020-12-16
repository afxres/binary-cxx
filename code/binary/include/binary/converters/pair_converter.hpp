#pragma once

#include "__length_calculator.hpp"

namespace mikodev::binary::converters
{
    template <typename _TyK, typename _TyV>
    class pair_converter : public abstract_converter<std::pair<_TyK, _TyV>>
    {
    private:
        using item_t = std::pair<_TyK, _TyV>;

        using converter_ptr_pair = std::pair<abstract_converter_ptr<_TyK>, abstract_converter_ptr<_TyV>>;

        using calculator_t = __length_calculator<converter_ptr_pair, 2>;

        converter_ptr_pair converters_;

    public:
        pair_converter(converter_ptr_pair converters) : abstract_converter<item_t>::abstract_converter(calculator_t::invoke(converters)), converters_(converters) {}

        virtual void encode(allocator& allocator, const item_t& item) override
        {
            std::get<0>(converters_)->encode_auto(allocator, std::get<0>(item));
            std::get<1>(converters_)->encode(allocator, std::get<1>(item));
        }

        virtual item_t decode(const span& span) override
        {
            auto view(span);
            auto k = std::get<0>(converters_)->decode_auto(view);
            auto v = std::get<1>(converters_)->decode(view);
            return std::make_pair(std::move(k), std::move(v));
        }

        virtual void encode_auto(allocator& allocator, const item_t& item) override
        {
            std::get<0>(converters_)->encode_auto(allocator, std::get<0>(item));
            std::get<1>(converters_)->encode_auto(allocator, std::get<1>(item));
        }

        virtual item_t decode_auto(span& span) override
        {
            auto k = std::get<0>(converters_)->decode_auto(span);
            auto v = std::get<1>(converters_)->decode_auto(span);
            return std::make_pair(std::move(k), std::move(v));
        }
    };
}
