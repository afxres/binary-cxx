#include "binary/external/BinaryModule.hpp"

#include <cassert>
#include <cstring>

namespace binary::external {
using BIN1 = uint8_t;
using BIN2 = uint16_t;
using BIN4 = uint32_t;
using BIN8 = uint64_t;

template <typename Item>
Item LoadUnaligned(const std::byte* source, size_t offset) {
    Item item;
    memcpy(&item, source + offset, sizeof(Item));
    return item;
}

LongDataSlot GetLongData(const std::span<const std::byte>& span) {
    const std::byte* source = span.data();
    const size_t length = span.size();
    assert(length <= 0x0F);
    uint64_t tail = (length & 8U) == 0 ? 0UL : LoadUnaligned<BIN8>(source, length & 7U);
    uint64_t head = (length & 4U) == 0 ? 0UL : LoadUnaligned<BIN4>(source, length & 3U);
    if ((length & 2U) != 0) {
        head = (head << 0x10U) | LoadUnaligned<BIN2>(source, length & 1U);
    }
    if ((length & 1U) != 0) {
        head = (head << 0x08U) | LoadUnaligned<BIN1>(source, length & 0U);
    }
    return LongDataSlot{.Head = (head << 0x08U) | static_cast<uint8_t>(length), .Tail = tail};
}
}
