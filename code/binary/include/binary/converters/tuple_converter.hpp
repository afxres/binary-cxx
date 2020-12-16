#pragma once

#include "../abstract_converter.hpp"

#include <memory>
#include <tuple>
#include <vector>

namespace mikodev::binary::converters
{
    template <typename ... TArgs>
    class tuple_converter : public abstract_converter<std::tuple<TArgs ...>>
    {
    private:
        static constexpr size_t __tuple_size = sizeof ... (TArgs);

        template <typename TCvts, typename TElms, bool IsAuto, size_t Is>
        struct _adapter
        {
            static void encode(allocator& allocator, const TElms& item, const TCvts& converters)
            {
                auto c = std::get<Is>(converters);
                if constexpr (!IsAuto && Is == __tuple_size - 1)
                    c->encode(allocator, std::get<Is>(item));
                else
                    c->encode_auto(allocator, std::get<Is>(item));
                if constexpr (Is != __tuple_size - 1)
                    _adapter<TCvts, TElms, IsAuto, Is + 1>::encode(allocator, item, converters);
            }

            static auto decode(span& span, const TCvts& converters)
            {
                auto c = std::get<Is>(converters);
                auto i = (!IsAuto && Is == __tuple_size - 1)
                    ? c->decode(span)
                    : c->decode_auto(span);
                auto t = std::make_tuple(std::move(i));
                if constexpr (Is == __tuple_size - 1)
                    return t;
                else
                    return std::tuple_cat(std::move(t), _adapter<TCvts, TElms, IsAuto, Is + 1>::decode(span, converters));
            }
        };

        template <typename TCvts, size_t Is>
        struct _counter
        {
            static void select_length(std::vector<length_t>& vector, const TCvts& converters)
            {
                vector.push_back(std::get<Is>(converters)->length());
                if constexpr (Is != __tuple_size - 1)
                    _counter<TCvts, Is + 1>::select_length(vector, converters);
            }
        };

        using tuple_converter_ptr = std::tuple<abstract_converter_ptr<TArgs> ...>;

        using adapter_t = _adapter<tuple_converter_ptr, std::tuple<TArgs ...>, false, 0>;

        using adapter_auto_t = _adapter<tuple_converter_ptr, std::tuple<TArgs ...>, true, 0>;

        length_t __length(tuple_converter_ptr converters)
        {
            std::vector<length_t> vector;
            _counter<tuple_converter_ptr, 0>::select_length(vector, converters);
            if (std::find(vector.begin(), vector.end(), 0) != vector.end())
                return 0;
            length_t size = 0;
            for (length_t i : vector)
                size += i;
            return size;
        }

        tuple_converter_ptr converters_;

    public:
        tuple_converter(std::tuple<abstract_converter_ptr<TArgs> ...> converters) : abstract_converter<std::tuple<TArgs ...>>::abstract_converter(__length(converters)), converters_(converters) {}

        tuple_converter(abstract_converter_ptr<TArgs> ... converters) : tuple_converter(std::make_tuple(converters ...)) {}

        virtual void encode(allocator& allocator, const std::tuple<TArgs ...>& item) override
        {
            adapter_t::encode(allocator, item, converters_);
        }

        virtual void encode_auto(allocator& allocator, const std::tuple<TArgs ...>& item) override
        {
            adapter_auto_t::encode(allocator, item, converters_);
        }

        virtual std::tuple<TArgs ...> decode(const span& span) override
        {
            binary::span view = span;
            return adapter_t::decode(view, converters_);
        }

        virtual std::tuple<TArgs ...> decode_auto(span& span) override
        {
            return adapter_auto_t::decode(span, converters_);
        }
    };
}
