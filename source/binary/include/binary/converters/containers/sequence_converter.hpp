#pragma once

#include "../../converter_base.hpp"

#include <memory>

#include <list>
#include <deque>
#include <vector>

namespace mikodev::binary::converters::containers
{
    template <typename _Def, typename _Ty, typename _Alloc>
    class sequence_converter : public converter_base<_Def>
    {
    private:
        std::shared_ptr<converter_base<_Ty>> _converter;

    public:
        sequence_converter(std::shared_ptr<converter_base<_Ty>> converter) : _converter(converter) {}

        virtual void encode(allocator_base& allocator, const _Def& item) override
        {
            converter_base<_Ty>& converter = *(_converter.get());
            for (const _Ty& i : item)
                converter.encode_auto(allocator, i);
        }

        virtual _Def decode(const span_view_base& span) override
        {
            std::shared_ptr<span_view_base> view = span.clone();
            span_view_base& data = *(view.get());
            converter_base<_Ty>& converter = *(_converter.get());
            _Def item;
            while (data.size() != 0)
                item.push_back(converter.decode_auto(data));
            return item;
        }
    };

    template <template<typename, typename> typename _Container, typename _Ty, typename _Alloc = std::allocator<_Ty>>
    using container_converter_t = sequence_converter<typename std::enable_if<
        std::is_same<_Container<_Ty, _Alloc>, std::list<_Ty, _Alloc>>::value ||
        std::is_same<_Container<_Ty, _Alloc>, std::deque<_Ty, _Alloc>>::value ||
        std::is_same<_Container<_Ty, _Alloc>, std::vector<_Ty, _Alloc>>::value, _Container<_Ty, _Alloc>>::type, _Ty, _Alloc>;
}
