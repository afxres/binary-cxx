#pragma once

#include "../allocator_base.hpp"
#include "../allocator_helper.hpp"
#include "../converter_base.hpp"
#include "../primitive_helper.hpp"
#include "../span_view.hpp"
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
            allocator_helper::append(allocator, item.c_str(), item.size());
        }

        virtual std::string decode(const span_view& span) override
        {
            return std::string(reinterpret_cast<const char*>(span.data()), span.size());
        }

        virtual void encode_with_length_prefix(allocator_base& allocator, const std::string& item) override
        {
            size_t size = item.size();
            primitive_helper::encode_number(allocator, size);
            allocator_helper::append(allocator, item.c_str(), size);
        }

        virtual std::string decode_with_length_prefix(span_view& span) override
        {
            // use helper class for length prefix
            span_view view = primitive_helper::decode_buffer_with_length_prefix(span);
            return std::string(reinterpret_cast<const char*>(view.data()), view.size());
        }
    };
}
