#pragma once

#include "../../abstract_converter.hpp"

namespace mikodev::binary::converters::containers
{
    template <typename _Container, typename _Element, template<typename, typename> typename _Adder, template<typename, typename> typename _Counter>
    class __basic_container_converter : public abstract_converter<_Container>
    {
    private:
        abstract_converter_ptr<_Element> converter_;

    public:
        __basic_container_converter(abstract_converter_ptr<_Element> converter) : converter_(converter) {}

        virtual void encode(allocator& allocator, const _Container& item) override
        {
            abstract_converter<_Element>& converter = *converter_;
            for (const _Element& i : item)
                converter.encode_auto(allocator, i);
        }

        virtual _Container decode(const span& span) override
        {
            binary::span data = span;
            abstract_converter<_Element>& converter = *converter_;
            _Container container{};
            _Counter<_Container, _Element>::reserve(container, converter, data);
            while (data.length() != 0)
                _Adder<_Container, _Element>::add(container, converter.decode_auto(data));
            return container;
        }
    };
}
