#pragma once

#include "../converter_base.hpp"

#include <list>
#include <memory>
#include <vector>

namespace mikodev::binary::converters
{
    template <template<typename, typename> typename _Container, typename _Ty, typename _Alloc = std::allocator<_Ty>>
    class container_converter : public converter_base<_Container<_Ty, _Alloc>>
    {
    private:
        template <template<typename, typename> typename _Def>
        struct _adapter
        {
            static void add(_Def<_Ty, _Alloc>& container, _Ty&& item);
        };

        template <>
        struct _adapter<std::list>
        {
            static void add(std::list<_Ty, _Alloc>& container, _Ty&& item) { container.push_back(item); }
        };

        template <>
        struct _adapter<std::vector>
        {
            static void add(std::vector<_Ty, _Alloc>& container, _Ty&& item) { container.push_back(item); }
        };

        std::shared_ptr<converter_base<_Ty>> _converter;

    public:
        container_converter(std::shared_ptr<converter_base<_Ty>> converter) : _converter(converter) {}

        virtual void encode(allocator_base& allocator, const _Container<_Ty, _Alloc>& item) override
        {
            converter_base<_Ty>& converter = *(_converter.get());
            for (const _Ty& i : item)
                converter.encode_auto(allocator, i);
        }

        virtual _Container<_Ty, _Alloc> decode(const span_view_base& span) override
        {
            std::shared_ptr<span_view_base> view = span.clone();
            span_view_base& data = *(view.get());
            converter_base<_Ty>& converter = *(_converter.get());
            _Container<_Ty, _Alloc> item;
            while (data.size() != 0)
                _adapter<_Container>::add(item, converter.decode_auto(data));
            return item;
        }
    };
}
