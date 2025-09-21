#ifndef BINARY_EXTERNAL_LONGDATASLOT_HPP
#define BINARY_EXTERNAL_LONGDATASLOT_HPP

#include <cstdint>

namespace binary::external {
struct LongDataSlot {
    uint64_t Head;
    uint64_t Tail;
};
}

#endif
