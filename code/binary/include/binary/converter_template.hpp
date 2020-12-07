#pragma once

#include "allocator_base.hpp"
#include "converter_abstract.hpp"
#include "span_view_base.hpp"

namespace mikodev::binary
{
    template <typename T>
    class converter_template : public converter_abstract
    {
    public:
        using converter_abstract::converter_abstract;

        virtual void encode(allocator_base& allocator, const T& item) = 0;

        virtual T decode(const span_view_base& span) = 0;

        virtual void encode_auto(allocator_base& allocator, const T& item) = 0;

        virtual T decode_auto(span_view_base& span) = 0;

        virtual void encode_with_length_prefix(allocator_base& allocator, const T& item) = 0;

        virtual T decode_with_length_prefix(span_view_base& span) = 0;
    };
}
