#pragma once

#include "allocator_base.hpp"
#include "converter_abstract.hpp"
#include "primitive_helper.hpp"
#include "span_view.hpp"

namespace mikodev::binary
{
    template <typename T>
    class converter_base : public converter_abstract
    {
    public:
        converter_base() : converter_abstract(0) {}

        converter_base(size_t byte_size) : converter_abstract(byte_size) {}

        virtual void encode(allocator_base& allocator, const T& item) = 0;

        virtual T decode(const span_view& span) = 0;

        virtual void encode_auto(allocator_base& allocator, const T& item)
        {
            auto size = this->byte_size();
            if (size == 0)
            {
                encode_with_length_prefix(allocator, item);
            }
            else
            {
                this->encode(allocator, item);
            }
        }

        virtual T decode_auto(span_view& span)
        {
            auto size = this->byte_size();
            if (size == 0)
            {
                return decode_with_length_prefix(span);
            }
            else
            {
                auto result = this->decode(span);
                span = span.slice(size);
                return result;
            }
        }

        virtual void encode_with_length_prefix(allocator_base& allocator, const T& item)
        {
            auto size = this->byte_size();
            if (size == 0)
            {
                auto anchor = allocator_helper::anchor_length_prefix(allocator);
                encode(allocator, item);
                allocator_helper::append_length_prefix(allocator, anchor);
            }
            else
            {
                primitive_helper::encode_number(allocator, size);
                encode(allocator, item);
            }
        }

        virtual T decode_with_length_prefix(span_view& span)
        {
            return decode(primitive_helper::decode_buffer_with_length_prefix(span));
        }
    };
}
