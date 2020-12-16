#pragma once

#include "../../abstract_converter.hpp"

#include <memory>

namespace mikodev::binary::converters::containers
{
    template <typename _Container, typename _Kty, typename _Vty>
    class __basic_pair_container_converter : public abstract_converter<_Container>
    {
    private:
        std::pair<abstract_converter_ptr<_Kty>, abstract_converter_ptr<_Vty>> converters_;

    public:
        __basic_pair_container_converter(std::pair<abstract_converter_ptr<_Kty>, abstract_converter_ptr<_Vty>> converters) : converters_(converters) {}

        __basic_pair_container_converter(abstract_converter_ptr<_Kty> converter_1, abstract_converter_ptr<_Vty> converter_2) : __basic_pair_container_converter(std::make_pair(converter_1, converter_2)) {}

        virtual void encode(allocator& allocator, const _Container& item) override
        {
            auto& converter_1 = *(converters_.first);
            auto& converter_2 = *(converters_.second);
            for (const std::pair<const _Kty, _Vty>& i : item)
            {
                const _Kty& k = i.first;
                const _Vty& v = i.second;
                converter_1.encode_auto(allocator, k);
                converter_2.encode_auto(allocator, v);
            }
        }

        virtual _Container decode(const span& span) override
        {
            binary::span data = span;
            auto& converter_1 = *(converters_.first);
            auto& converter_2 = *(converters_.second);
            _Container container{};
            while (data.length() != 0)
            {
                _Kty k = converter_1.decode_auto(data);
                _Vty v = converter_2.decode_auto(data);
                container.emplace(std::move(k), std::move(v));
            }
            return container;
        }
    };
}
