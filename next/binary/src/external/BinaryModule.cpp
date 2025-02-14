#include "binary/external/BinaryModule.hpp"

#include <cassert>

namespace binary::external {
template <typename T>
uint64_t __load_slot__(const std::byte* source, size_t length) {
    if ((length & sizeof(T)) == 0) {
        return 0;
    }
    return static_cast<uint64_t>(*reinterpret_cast<const T*>(source + (length & (sizeof(T) - 1)))) << ((sizeof(uint64_t) - sizeof(T)) * 8);
}

LongDataSlot GetLongData(const std::span<const std::byte>& span) {
    auto source = span.data();
    auto length = span.size();
    assert(length <= 0x0F);
    uint64_t head = __load_slot__<uint64_t>(source, length);
    uint64_t tail = __load_slot__<uint32_t>(source, length) | __load_slot__<uint16_t>(source, length) | __load_slot__<uint8_t>(source, length) | length;
    return LongDataSlot{.Head = head, .Tail = tail};
}
}
