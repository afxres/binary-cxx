#include "binary/external/HashCodeList.hpp"

#include <cstdint>

namespace binary::external {
HashCodeList::HashCodeList(std::unordered_map<std::string_view, size_t>&& record)
    : record(std::move(record)) {}

size_t HashCodeList::Invoke(const std::span<const std::byte>& span) {
    const auto& record = this->record;
    std::string_view view(reinterpret_cast<const char*>(span.data()), span.size());
    auto iterator = record.find(view);
    if (iterator != record.end()) {
        return iterator->second;
    }
    return SIZE_MAX;
}
}
