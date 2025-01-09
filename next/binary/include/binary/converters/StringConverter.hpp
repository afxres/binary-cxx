#pragma once

#ifndef BINARY_CONVERTERS_STRINGCONVERTER_HPP
#define BINARY_CONVERTERS_STRINGCONVERTER_HPP

#include <string>

#include "binary/Converter.hpp"

namespace binary::converters {
class StringConverter : public Converter<std::string> {
public:
    virtual void Encode(Allocator& allocator, const std::string& item) override {
        allocator.Append(std::span<const std::byte>(reinterpret_cast<const std::byte*>(item.data()), item.size()));
    }

    virtual std::string Decode(const std::span<const std::byte>& span) override {
        return std::string(reinterpret_cast<const char*>(span.data()), span.size());
    }
};
}

#endif
