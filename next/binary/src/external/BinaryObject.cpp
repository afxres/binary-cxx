#include "binary/external/BinaryObject.hpp"

#include <algorithm>
#include <cassert>
#include <stdexcept>

#include <binary/external/BinaryDefine.hpp>
#include <binary/external/BinaryModule.hpp>

namespace binary::external {
std::unique_ptr<ByteViewList> CreateByteViewList(const std::vector<std::vector<std::byte>>& items, size_t& error) {
    assert(items.size() != 0);
    if (items.size() <= LongDataListItemCountLimits && std::all_of(items.begin(), items.end(), [](const auto& x) { return x.size() <= LongDataListItemBytesLimits; })) {
        return CreateLongDataList(items, error);
    } else {
        return CreateHashCodeList(items, error);
    }
}

std::unique_ptr<LongDataList> CreateLongDataList(const std::vector<std::vector<std::byte>>& items, size_t& error) {
    std::vector<LongDataSlot> result;
    for (const auto& span : items) {
        if (span.size() > LongDataListItemBytesLimits) {
            throw std::logic_error("invalid span size");
        }
        auto slot = GetLongData(span);
        if (std::find_if(result.begin(), result.end(), [slot](const auto& x) { return x.Head == slot.Head && x.Tail == slot.Tail; }) != result.end()) {
            error = result.size();
            return nullptr;
        }
        result.emplace_back(slot);
    }
    error = SIZE_MAX;
    return std::make_unique<LongDataList>(std::move(result));
}

std::unique_ptr<HashCodeList> CreateHashCodeList(const std::vector<std::vector<std::byte>>& items, size_t& error) {
    std::unordered_map<std::string_view, size_t> result;
    for (const auto& span : items) {
        size_t cursor = items.size();
        std::string_view view(reinterpret_cast<const char*>(span.data()), span.size());
        if (!result.try_emplace(view, cursor).second) {
            error = cursor;
            return nullptr;
        }
    }
    error = SIZE_MAX;
    return std::make_unique<HashCodeList>(std::move(result));
}
}
