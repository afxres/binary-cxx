#pragma once

#include "../abstract_converter.hpp"

#include <string>

namespace mikodev::binary::converters {
/* string converter (copy memory directly) */
class string_converter : public abstract_converter<std::string> {
public:
    virtual void encode(allocator& allocator, const std::string& item) override {
        allocator::append(allocator, reinterpret_cast<const_byte_ptr>(item.data()), static_cast<length_t>(item.size()));
    }

    virtual std::string decode(const span& span) override {
        return std::string(reinterpret_cast<const char*>(span.buffer()), static_cast<size_t>(span.length()));
    }
};
}
