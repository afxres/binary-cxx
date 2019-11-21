#pragma once

#include "../converter_base.hpp"

#include <memory>
#include <vector>

namespace mikodev::binary::converters
{
    template <typename T>
    class vector_converter : public converter_base<std::vector<T>>
    {
    private:
        std::shared_ptr<converter_base<T>> _converter;

    public:
        vector_converter(std::shared_ptr<converter_base<T>> converter) : _converter(converter) {}

        virtual void encode(allocator_base& allocator, const std::vector<T>& item) override
        {
            converter_base<T>* converter = _converter.get();
            for (const T& i : item)
                converter->encode_auto(allocator, i);
        }

        virtual std::vector<T> decode(const span_view_base& span) override
        {
            std::shared_ptr<span_view_base> view = span.clone();
            std::vector<T> item;
            span_view_base* data = view.get();
            converter_base<T>* converter = _converter.get();
            while (data->size() != 0)
                item.push_back(converter->decode_auto(*data));
            return item;
        }
    };
}
