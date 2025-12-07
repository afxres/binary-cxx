#include "binary/external/BinaryObject.hpp"

#include <algorithm>
#include <cassert>

#include <binary/external/BinaryDefine.hpp>
#include <binary/external/BinaryModule.hpp>

namespace binary::external {
std::tuple<size_t, std::unique_ptr<ByteViewList>> CreateByteViewList(const std::vector<std::vector<std::byte>>& items) {
    assert(items.size() != 0);
    auto raw = CreateLongDataList(items);
    if (std::get<0>(raw) == SIZE_MAX && std::get<1>(raw) == nullptr) {
        return CreateHashCodeList(items);
    }
    return raw;
}

std::tuple<size_t, std::unique_ptr<LongDataList>> CreateLongDataList(const std::vector<std::vector<std::byte>>& items) {
    if (items.size() > LongDataListItemCountLimits) {
        return {SIZE_MAX, nullptr};
    }
    std::vector<LongDataSlot> result;
    for (const auto& span : items) {
        if (span.size() > LongDataListItemBytesLimits) {
            return {SIZE_MAX, nullptr};
        }
        auto slot = GetLongData(span);
        if (std::ranges::find_if(result, [slot](const auto& x) { return x.Head == slot.Head && x.Tail == slot.Tail; }) != result.end()) {
            return {result.size(), nullptr};
        }
        result.emplace_back(slot);
    }
    return {SIZE_MAX, std::make_unique<LongDataList>(std::move(result))};
}

std::tuple<size_t, std::unique_ptr<HashCodeList>> CreateHashCodeList(const std::vector<std::vector<std::byte>>& items) {
    std::unordered_map<std::string_view, size_t> result;
    for (const auto& span : items) {
        size_t cursor = result.size();
        std::string_view view(reinterpret_cast<const char*>(span.data()), span.size());
        if (!result.try_emplace(view, cursor).second) {
            return {cursor, nullptr};
        }
    }
    return {SIZE_MAX, std::make_unique<HashCodeList>(std::move(result))};
}
}
