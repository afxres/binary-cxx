#pragma once

#include "converter_template.hpp"
#include "primitive_helper.hpp"

namespace mikodev::binary
{
    template <typename T>
    class converter_base : public converter_template<T>
    {
    public:
        using converter_template<T>::converter_template;

        virtual void encode_auto(allocator_base& allocator, const T& item)
        {
            size_t size = static_cast<converter_abstract*>(this)->size();
            if (size == 0)
            {
                encode_with_length_prefix(allocator, item);
            }
            else
            {
                static_cast<converter_template<T>*>(this)->encode(allocator, item);
            }
        }

        virtual T decode_auto(span_view_base& span)
        {
            size_t size = static_cast<converter_abstract*>(this)->size();
            if (size == 0)
            {
                return decode_with_length_prefix(span);
            }
            else
            {
                T result = static_cast<converter_template<T>*>(this)->decode(span);
                span.slice_this(size);
                return result;
            }
        }

        virtual void encode_with_length_prefix(allocator_base& allocator, const T& item)
        {
            size_t size = static_cast<converter_abstract*>(this)->size();
            if (size == 0)
            {
                allocator_length_prefix_anchor_t anchor = allocator_helper::anchor_length_prefix(allocator);
                static_cast<converter_template<T>*>(this)->encode(allocator, item);
                allocator_helper::append_length_prefix(allocator, anchor);
            }
            else
            {
                primitive_helper::encode_number(allocator, size);
                static_cast<converter_template<T>*>(this)->encode(allocator, item);
            }
        }

        virtual T decode_with_length_prefix(span_view_base& span)
        {
            // lifetime management via smart pointer
            std::unique_ptr<span_view_base> view = primitive_helper::decode_buffer_with_length_prefix(span);
            return static_cast<converter_template<T>*>(this)->decode(*view);
        }
    };
}
