#pragma once

#include "../converter_base.hpp"

namespace mikodev::binary::converters
{
    template <typename _Ty1, class _Ty2>
    class pair_converter : public converter_base<std::pair<_Ty1, _Ty2>>
    {
    private:
        static size_t _size(std::pair<std::shared_ptr<converter_base<_Ty1>>, std::shared_ptr<converter_base<_Ty2>>> converters)
        {
            size_t size_1 = converters.first->size();
            size_t size_2 = converters.second->size();
            if (size_1 == 0 || size_2 == 0)
                return 0;
            return size_1 + size_2;
        }

        std::pair<std::shared_ptr<converter_base<_Ty1>>, std::shared_ptr<converter_base<_Ty2>>> _converters;

    public:
        pair_converter(std::pair<std::shared_ptr<converter_base<_Ty1>>, std::shared_ptr<converter_base<_Ty2>>> converters) : converter_base(_size(converters)), _converters(converters) {}

        pair_converter(std::shared_ptr<converter_base<_Ty1>> converter_1, std::shared_ptr<converter_base<_Ty2>> converter_2) : pair_converter(std::make_pair(converter_1, converter_2)) {}

        virtual void encode(allocator_base& allocator, const std::pair<_Ty1, _Ty2>& item) override
        {
            converter_base<_Ty1>& converter_1 = *(_converters.first);
            converter_base<_Ty2>& converter_2 = *(_converters.second);
            converter_1.encode_auto(allocator, item.first);
            converter_2.encode(allocator, item.second);
        }

        virtual std::pair<_Ty1, _Ty2> decode(const span_view_base& span) override
        {
            converter_base<_Ty1>& converter_1 = *(_converters.first);
            converter_base<_Ty2>& converter_2 = *(_converters.second);
            std::unique_ptr<span_view_base> view = span.clone();
            _Ty1 item_1 = converter_1.decode_auto(*view);
            _Ty2 item_2 = converter_2.decode(*view);
            return std::make_pair(item_1, item_2);
        }

        virtual void encode_auto(allocator_base& allocator, const std::pair<_Ty1, _Ty2>& item) override
        {
            converter_base<_Ty1>& converter_1 = *(_converters.first);
            converter_base<_Ty2>& converter_2 = *(_converters.second);
            converter_1.encode_auto(allocator, item.first);
            converter_2.encode_auto(allocator, item.second);
        }

        virtual std::pair<_Ty1, _Ty2> decode_auto(span_view_base& span) override
        {
            converter_base<_Ty1>& converter_1 = *(_converters.first);
            converter_base<_Ty2>& converter_2 = *(_converters.second);
            _Ty1 item_1 = converter_1.decode_auto(span);
            _Ty2 item_2 = converter_2.decode_auto(span);
            return std::make_pair(item_1, item_2);
        }
    };
}
