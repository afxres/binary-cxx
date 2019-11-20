#pragma once

#include "../allocator_base.hpp"
#include "../converter_base.hpp"
#include "../span_view.hpp"
#include "../exceptions/throw_helper.hpp"

#include <string>

namespace mikodev::binary::converters
{
    class string_converter : public converter_base<std::string>
    {
    public:
        virtual void encode(allocator_base& allocator, const std::string& item) override
        {
            std::byte* location = allocator.allocate(item.size());
            std::memcpy(location, item.c_str(), item.size());
        }

        virtual std::string decode(const span_view& span) override
        {
            return std::string(reinterpret_cast<const char*>(span.data()), span.size());
        }
    };
}
