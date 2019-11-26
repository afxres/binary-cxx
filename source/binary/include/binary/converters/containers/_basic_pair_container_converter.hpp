#pragma once

#include "../../converter_base.hpp"

#include <memory>

namespace mikodev::binary::converters::containers
{
    template <typename _Container, typename _Kty, typename _Vty>
    class _basic_pair_container_converter : public converter_base<_Container>
    {
    private:
        std::pair<std::shared_ptr<converter_base<_Kty>>, std::shared_ptr<converter_base<_Vty>>> _converters;

    public:
        _basic_pair_container_converter(std::pair<std::shared_ptr<converter_base<_Kty>>, std::shared_ptr<converter_base<_Vty>>> converters) : _converters(converters) {}

        _basic_pair_container_converter(std::shared_ptr<converter_base<_Kty>> converter_1, std::shared_ptr<converter_base<_Vty>> converter_2) : _basic_pair_container_converter(std::make_pair(converter_1, converter_2)) {}

        virtual void encode(allocator_base& allocator, const _Container& item) override
        {
            converter_base<_Kty>& converter_1 = *(_converters.first);
            converter_base<_Vty>& converter_2 = *(_converters.second);
            for (const std::pair<const _Kty, _Vty>& i : item)
            {
                const _Kty& k = i.first;
                const _Vty& v = i.second;
                converter_1.encode_auto(allocator, k);
                converter_2.encode_auto(allocator, v);
            }
        }

        virtual _Container decode(const span_view_base& span) override
        {
            std::shared_ptr<span_view_base> view = span.clone();
            span_view_base& data = *view;
            converter_base<_Kty>& converter_1 = *(_converters.first);
            converter_base<_Vty>& converter_2 = *(_converters.second);
            _Container container;
            while (data.size() != 0)
            {
                _Kty k = converter_1.decode_auto(data);
                _Vty v = converter_2.decode_auto(data);
                container.emplace(std::move(k), std::move(v));
            }
            return container;
        }
    };
}
