#pragma once

#include "../abstract_converter.hpp"

#include <memory>

namespace mikodev::binary::converters
{
    template <typename Container, typename Key, typename Value>
    class basic_pair_container_converter : public abstract_converter<Container>
    {
    private:
        using item_t = Container;

        using converter_ptr_pair = std::pair<abstract_converter_ptr<Key>, abstract_converter_ptr<Value>>;

        converter_ptr_pair converters_;

    public:
        basic_pair_container_converter(converter_ptr_pair converters) : converters_(converters) {}

        virtual void encode(allocator& allocator, const item_t& item) override
        {
            auto& a = *(std::get<0>(converters_));
            auto& b = *(std::get<1>(converters_));
            for (const auto& i : item)
            {
                const auto& k = std::get<0>(i);
                const auto& v = std::get<1>(i);
                a.encode_auto(allocator, k);
                b.encode_auto(allocator, v);
            }
        }

        virtual item_t decode(const span& span) override
        {
            auto data(span);
            auto& a = *(std::get<0>(converters_));
            auto& b = *(std::get<1>(converters_));
            item_t container{};
            while (data.length() != 0)
            {
                auto k = a.decode_auto(data);
                auto v = b.decode_auto(data);
                container.emplace(std::move(k), std::move(v));
            }
            return container;
        }
    };
}
