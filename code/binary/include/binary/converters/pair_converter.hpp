#pragma once

#include "../abstract_converter.hpp"

namespace mikodev::binary::converters
{
    template <typename _Ty1, class _Ty2>
    class pair_converter : public abstract_converter<std::pair<_Ty1, _Ty2>>
    {
    private:
        using cvt1 = abstract_converter<_Ty1>;

        using cvt2 = abstract_converter<_Ty2>;

        using cvt1_ptr = abstract_converter_ptr<_Ty1>;

        using cvt2_ptr = abstract_converter_ptr<_Ty2>;

        static length_t length__(std::pair<cvt1_ptr, cvt2_ptr> converters)
        {
            length_t length_1 = converters.first->length();
            length_t length_2 = converters.second->length();
            if (length_1 == 0 || length_2 == 0)
                return 0;
            return length_1 + length_2;
        }

        std::pair<cvt1_ptr, cvt2_ptr> _converters;

    public:
        pair_converter(std::pair<abstract_converter_ptr<_Ty1>, abstract_converter_ptr<_Ty2>> converters) : abstract_converter<std::pair<_Ty1, _Ty2>>::abstract_converter(length__(converters)), _converters(converters) {}

        pair_converter(abstract_converter_ptr<_Ty1> converter_1, abstract_converter_ptr<_Ty2> converter_2) : pair_converter(std::make_pair(converter_1, converter_2)) {}

        virtual void encode(allocator& allocator, const std::pair<_Ty1, _Ty2>& item) override
        {
            cvt1& converter_1 = *(_converters.first);
            cvt2& converter_2 = *(_converters.second);
            converter_1.encode_auto(allocator, item.first);
            converter_2.encode(allocator, item.second);
        }

        virtual std::pair<_Ty1, _Ty2> decode(const span& span) override
        {
            cvt1& converter_1 = *(_converters.first);
            cvt2& converter_2 = *(_converters.second);
            binary::span view = span;
            _Ty1 item_1 = converter_1.decode_auto(view);
            _Ty2 item_2 = converter_2.decode(view);
            return std::make_pair(item_1, item_2);
        }

        virtual void encode_auto(allocator& allocator, const std::pair<_Ty1, _Ty2>& item) override
        {
            cvt1& converter_1 = *(_converters.first);
            cvt2& converter_2 = *(_converters.second);
            converter_1.encode_auto(allocator, item.first);
            converter_2.encode_auto(allocator, item.second);
        }

        virtual std::pair<_Ty1, _Ty2> decode_auto(span& span) override
        {
            cvt1& converter_1 = *(_converters.first);
            cvt2& converter_2 = *(_converters.second);
            _Ty1 item_1 = converter_1.decode_auto(span);
            _Ty2 item_2 = converter_2.decode_auto(span);
            return std::make_pair(item_1, item_2);
        }
    };
}
