#include "binary/external/BinaryModule.hpp"

#include <cassert>

namespace binary::external {
using BIN1 = uint8_t;
using BIN2 = uint16_t;
using BIN4 = uint32_t;
using BIN8 = uint64_t;

template <typename T>
T __load__(const std::byte* source, size_t offset) {
    return *reinterpret_cast<const T*>(source + offset);
}

LongDataSlot GetLongData(const std::span<const std::byte>& span) {
    const std::byte* source = span.data();
    const size_t length = span.size();
    assert(length <= 0x0F);
    uint64_t tail = (length & 8) == 0 ? 0UL : __load__<BIN8>(source, length & 7);
    uint64_t head = (length & 4) == 0 ? 0UL : __load__<BIN4>(source, length & 3);
    if ((length & 2) != 0) {
        head = (head << 0x10) | __load__<BIN2>(source, length & 1);
    }
    if ((length & 1) != 0) {
        head = (head << 0x08) | __load__<BIN1>(source, length & 0);
    }
    return LongDataSlot{.Head = (head << 0x08) | (uint8_t)length, .Tail = tail};
}
}
