#pragma once

#include "../allocator_base.hpp"
#include "../converter_base.hpp"
#include "../span_view.hpp"
#include "../exceptions/throw_helper.hpp"

#include <memory>
#include <tuple>

namespace mikodev::binary::converters
{
    template <typename ... TArgs>
    class tuple_converter : public converter_base<std::tuple<TArgs ...>>
    {
    private:
        static constexpr auto _tuple_size = sizeof ... (TArgs);

        template <typename TCvts, typename TItem, std::size_t N>
        struct _adapter
        {
            static void encode(allocator_base& allocator, const TItem& item, const TCvts& converters)
            {
                if constexpr (N > 0)
                    _adapter<TCvts, TItem, N - 1>::encode(allocator, item, converters);
                auto c = std::get<N>(converters);
                auto i = std::get<N>(item);
                if constexpr (N == _tuple_size - 1)
                    c->encode(allocator, i);
                else
                    c->encode_auto(allocator, i);
            }

            static void encode_auto(allocator_base& allocator, const TItem& item, const TCvts& converters)
            {
                if constexpr (N > 0)
                    _adapter<TCvts, TItem, N - 1>::encode(allocator, item, converters);
                auto c = std::get<N>(converters);
                auto i = std::get<N>(item);
                c->encode_auto(allocator, i);
            }
        };

        using adapter = _adapter<std::tuple<std::shared_ptr<converter_base<TArgs>> ...>, std::tuple<TArgs ...>, _tuple_size - 1>;

        std::tuple<std::shared_ptr<converter_base<TArgs>> ...> _converters;

    public:
        tuple_converter(std::shared_ptr<converter_base<TArgs>> ... converters) : _converters(std::make_tuple(converters ...)) {}

        virtual void encode(allocator_base& allocator, const std::tuple<TArgs ...>& item) override
        {
            adapter::encode(allocator, item, _converters);
        }

        virtual void encode_auto(allocator_base& allocator, const std::tuple<TArgs ...>& item) override
        {
            adapter::encode_auto(allocator, item, _converters);
        }

        virtual std::tuple<TArgs ...> decode(const span_view& span) override
        {
            exceptions::throw_helper::throw_not_supported();
        }
    };
}
