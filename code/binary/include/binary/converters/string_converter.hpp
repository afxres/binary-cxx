#pragma once

#include "../allocator_helper.hpp"
#include "../converter_base.hpp"
#include "../primitive_helper.hpp"
#include "../exceptions/throw_helper.hpp"

#include <string>

namespace mikodev::binary::converters
{
    /* string converter (copy memory directly) */
    class string_converter : public converter_base<std::string>
    {
    public:
        virtual void encode(allocator_base& allocator, const std::string& item) override
        {
            allocator_helper::append(allocator, item.data(), item.size());
        }

        virtual std::string decode(const span_view_base& span) override
        {
            return std::string(reinterpret_cast<const char*>(span.data()), span.size());
        }

        virtual void encode_with_length_prefix(allocator_base& allocator, const std::string& item) override
        {
            size_t size = item.size();
            primitive_helper::encode_number(allocator, size);
            allocator_helper::append(allocator, item.data(), size);
        }

        virtual std::string decode_with_length_prefix(span_view_base& span) override
        {
            // lifetime management via smart pointer
            std::unique_ptr<span_view_base> view = primitive_helper::decode_buffer_with_length_prefix(span);
            return std::string(reinterpret_cast<const char*>(view->data()), view->size());
        }
    };
}