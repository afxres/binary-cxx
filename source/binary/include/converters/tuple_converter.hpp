#pragma once

#include "../converter_base.hpp"
#include "../exceptions/throw_helper.hpp"

#include <memory>
#include <tuple>
#include <vector>

namespace mikodev::binary::converters
{
    template <typename ... TArgs>
    class tuple_converter : public converter_base<std::tuple<TArgs ...>>
    {
    private:
        static constexpr size_t _TUPLE_SIZE = sizeof ... (TArgs);

        template <typename TCvts, typename TElms, bool IsAuto, size_t Is>
        struct _adapter
        {
            static void encode(allocator_base& allocator, const TElms& item, const TCvts& converters)
            {
                auto c = std::get<Is>(converters);
                auto i = std::get<Is>(item);
                if constexpr (!IsAuto && Is == _TUPLE_SIZE - 1)
                    c->encode(allocator, i);
                else
                    c->encode_auto(allocator, i);
                if constexpr (Is != _TUPLE_SIZE - 1)
                    _adapter<TCvts, TElms, IsAuto, Is + 1>::encode(allocator, item, converters);
            }

            static auto decode(span_view_base& span, const TCvts& converters)
            {
                auto c = std::get<Is>(converters);
                auto i = (!IsAuto && Is == _TUPLE_SIZE - 1)
                    ? c->decode(span)
                    : c->decode_auto(span);
                auto t = std::make_tuple(i);
                if constexpr (Is == _TUPLE_SIZE - 1)
                    return t;
                else
                    return std::tuple_cat(t, _adapter<TCvts, TElms, IsAuto, Is + 1>::decode(span, converters));
            }
        };

        template <typename TCvts, size_t Is>
        struct _counter
        {
            static void select_size(std::vector<size_t>& vector, const TCvts& converters)
            {
                vector.push_back(std::get<Is>(converters)->size());
                if constexpr (Is != _TUPLE_SIZE - 1)
                    _counter<TCvts, Is + 1>::select_size(vector, converters);
            }
        };

        using _tuple_converter_shared_ptr_t = std::tuple<std::shared_ptr<converter_base<TArgs>> ...>;

        using _adapter_t = _adapter<_tuple_converter_shared_ptr_t, std::tuple<TArgs ...>, false, 0>;

        using _adapter_auto_t = _adapter<_tuple_converter_shared_ptr_t, std::tuple<TArgs ...>, true, 0>;

        size_t _size(_tuple_converter_shared_ptr_t converters)
        {
            std::vector<size_t> vector;
            _counter< _tuple_converter_shared_ptr_t, 0>::select_size(vector, converters);
            if (std::find(vector.begin(), vector.end(), 0) != vector.end())
                return 0;
            size_t size = 0;
            for (size_t i : vector)
                size += i;
            return size;
        }

        _tuple_converter_shared_ptr_t _converters;

    public:
        tuple_converter(std::tuple<std::shared_ptr<converter_base<TArgs>> ...> converters) : converter_base(_size(converters)), _converters(converters) {}

        tuple_converter(std::shared_ptr<converter_base<TArgs>> ... converters) : tuple_converter(std::make_tuple(converters ...)) {}

        virtual void encode(allocator_base& allocator, const std::tuple<TArgs ...>& item) override
        {
            _adapter_t::encode(allocator, item, _converters);
        }

        virtual void encode_auto(allocator_base& allocator, const std::tuple<TArgs ...>& item) override
        {
            _adapter_auto_t::encode(allocator, item, _converters);
        }

        virtual std::tuple<TArgs ...> decode(const span_view_base& span) override
        {
            // lifetime management via smart pointer
            std::unique_ptr<span_view_base> view = span.clone();
            return _adapter_t::decode(*(view.get()), _converters);
        }

        virtual std::tuple<TArgs ...> decode_auto(span_view_base& span) override
        {
            return _adapter_auto_t::decode(span, _converters);
        }
    };
}
