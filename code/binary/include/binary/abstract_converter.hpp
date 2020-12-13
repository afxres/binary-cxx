#pragma once

#include "abstract_converter_interface.hpp"
#include "allocator.hpp"
#include "converter.hpp"
#include "span.hpp"

#include <memory>

namespace mikodev::binary
{
    template <typename T>
    class abstract_converter;

    template <typename T>
    using abstract_converter_ptr = std::shared_ptr<abstract_converter<T>>;

    template <typename T>
    class abstract_converter : public abstract_converter_interface
    {
    public:
        abstract_converter() : abstract_converter(0) {}

        abstract_converter(length_t length) : abstract_converter_interface(length) {}

        virtual void encode(allocator& allocator, const T& item) = 0;

        virtual void encode_auto(allocator& allocator, const T& item)
        {
            length_t length = static_cast<abstract_converter_interface*>(this)->length();
            if (length == 0)
            {
                this->encode_with_length_prefix(allocator, item);
            }
            else
            {
                this->encode(allocator, item);
            }
        }

        virtual void encode_with_length_prefix(allocator& allocator, const T& item)
        {
            length_t length = static_cast<abstract_converter_interface*>(this)->length();
            if (length == 0)
            {
                length_t anchor = allocator::anchor__(allocator, 4);
                this->encode(allocator, item);
                allocator::finish_anchor__(allocator, anchor);
            }
            else
            {
                number_t number = static_cast<number_t>(length);
                converter::encode(allocator, number);
                this->encode(allocator, item);
            }
        }

        virtual T decode(const span& span) = 0;

        virtual T decode_auto(span& span)
        {
            length_t length = static_cast<abstract_converter_interface*>(this)->length();
            if (length == 0)
            {
                return this->decode_with_length_prefix(span);
            }
            else
            {
                T result = this->decode(span);
                span = span.slice(length);
                return result;
            }
        }

        virtual T decode_with_length_prefix(span& span)
        {
            return this->decode(converter::decode_with_length_prefix(span));
        }
    };
}
