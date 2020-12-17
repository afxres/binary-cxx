#pragma once

#include "../abstract_converter.hpp"

namespace mikodev::binary::converters
{
    template <typename Container, typename Element, template<typename, typename> typename Adder, template<typename, typename> typename Counter>
    class basic_container_converter : public abstract_converter<Container>
    {
    private:
        using item_t = Container;

        using adder_t = Adder<Container, Element>;

        using counter_t = Counter<Container, Element>;

        using converter_ptr = abstract_converter_ptr<Element>;

        converter_ptr converter_;

    public:
        basic_container_converter(converter_ptr converter) : converter_(converter) {}

        virtual void encode(allocator& allocator, const item_t& item) override
        {
            auto& converter = *converter_;
            for (const auto& i : item)
                converter.encode_auto(allocator, i);
        }

        virtual item_t decode(const span& span) override
        {
            auto data(span);
            auto& converter = *converter_;
            item_t container{};
            counter_t::reserve(container, converter, data);
            while (data.length() != 0)
                adder_t::add(container, converter.decode_auto(data));
            return container;
        }
    };
}
