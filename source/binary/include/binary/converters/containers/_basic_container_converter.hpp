#pragma once

#include "../../converter_base.hpp"

#include <memory>

namespace mikodev::binary::converters::containers
{
    template <typename _Container, typename _Element, template<typename, typename> typename _Adder>
    class _basic_container_converter : public converter_base<_Container>
    {
    private:
        std::shared_ptr<converter_base<_Element>> _converter;

    public:
        _basic_container_converter(std::shared_ptr<converter_base<_Element>> converter) : _converter(converter) {}

        virtual void encode(allocator_base& allocator, const _Container& item) override
        {
            converter_base<_Element>& converter = *_converter;
            for (const _Element& i : item)
                converter.encode_auto(allocator, i);
        }

        virtual _Container decode(const span_view_base& span) override
        {
            std::shared_ptr<span_view_base> view = span.clone();
            span_view_base& data = *view;
            converter_base<_Element>& converter = *_converter;
            _Container container;
            while (data.size() != 0)
                _Adder<_Container, _Element>::add(container, converter.decode_auto(data));
            return container;
        }
    };
}
