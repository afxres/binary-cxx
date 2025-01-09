#include "binary/converters/StringConverter.hpp"

namespace binary::converters {
void StringConverter::Encode(Allocator& allocator, const std::string& item) {
    allocator.Append(std::span<const std::byte>(reinterpret_cast<const std::byte*>(item.data()), item.size()));
}

std::string StringConverter::Decode(const std::span<const std::byte>& span) {
    return std::string(reinterpret_cast<const char*>(span.data()), span.size());
}
}
