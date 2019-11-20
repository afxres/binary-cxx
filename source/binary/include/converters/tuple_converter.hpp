#pragma once

#include "../allocator_base.hpp"
#include "../converter_base.hpp"
#include "../span_view.hpp"
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
        static constexpr auto _tuple_size = sizeof ... (TArgs);

        template <typename TCvts, typename TItem, bool is_auto, size_t N>
        struct _adapter
        {
            static void encode(allocator_base& allocator, const TItem& item, const TCvts& converters)
            {
                auto c = std::get<N>(converters);
                auto i = std::get<N>(item);
                if constexpr (!is_auto && N == _tuple_size - 1)
                    c->encode(allocator, i);
                else
                    c->encode_auto(allocator, i);
                if constexpr (N != _tuple_size - 1)
                    _adapter<TCvts, TItem, is_auto, N + 1>::encode(allocator, item, converters);
            }

            static auto decode(span_view& span, const TCvts& converters)
            {
                auto c = std::get<N>(converters);
                auto i = (!is_auto && N == _tuple_size - 1)
                    ? c->decode(span)
                    : c->decode_auto(span);
                auto t = std::make_tuple(i);
                if constexpr (N == _tuple_size - 1)
                    return t;
                else
                    return std::tuple_cat(t, _adapter<TCvts, TItem, is_auto, N + 1>::decode(span, converters));
            }
        };

        template <typename TCvts, size_t N>
        struct _counter
        {
            static void select_size(std::vector<size_t>& vector, const TCvts& converters)
            {
                auto c = std::get<N>(converters);
                auto s = c->size();
                vector.push_back(s);
                if constexpr (N != _tuple_size - 1)
                    _counter<TCvts, N + 1>::select_size(vector, converters);
            }
        };

        using _tuple_converter_shared_ptr_t = std::tuple<std::shared_ptr<converter_base<TArgs>> ...>;

        using _adapter_t = _adapter<_tuple_converter_shared_ptr_t, std::tuple<TArgs ...>, false, 0>;

        using _adapter_auto_t = _adapter<_tuple_converter_shared_ptr_t, std::tuple<TArgs ...>, true, 0>;

        size_t _size(_tuple_converter_shared_ptr_t converters)
        {
            std::vector<size_t> vector;
            _counter< _tuple_converter_shared_ptr_t, 0>::select_size(vector, converters);
            auto end = vector.end();
            if (std::find(vector.begin(), end, 0) != end)
                return 0;
            size_t size = 0;
            for (auto i : vector)
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

        virtual std::tuple<TArgs ...> decode(const span_view& span) override
        {
            // copy as mutable
            span_view view = span;
            return _adapter_t::decode(view, _converters);
        }

        virtual std::tuple<TArgs ...> decode_auto(span_view& span) override
        {
            return _adapter_auto_t::decode(span, _converters);
        }
    };
}
