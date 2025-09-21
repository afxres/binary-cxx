#include "binary/external/LongDataList.hpp"

#include <algorithm>
#include <cassert>

#include "binary/external/BinaryDefine.hpp"
#include "binary/external/BinaryModule.hpp"

namespace binary::external {
LongDataList::LongDataList(std::vector<LongDataSlot>&& bits) {
    assert(bits.size() != 0);
    assert(std::all_of(bits.begin(), bits.end(), [](const auto& x) { return (x.Head & 0xFFU) <= LongDataListItemBytesLimits; }));
    assert(bits.size() <= LongDataListItemCountLimits);
    this->bits = std::move(bits);
}

size_t LongDataList::Invoke(const std::span<const std::byte>& span) {
    if (span.size() > LongDataListItemBytesLimits) {
        return SIZE_MAX;
    }
    auto data = GetLongData(span);
    const auto& bits = this->bits;
    for (size_t i = 0; i < bits.size(); i++) {
        const auto& item = bits.at(i);
        if (data.Head == item.Head && data.Tail == item.Tail) {
            return i;
        }
    }
    return SIZE_MAX;
}
}
