#ifndef BINARY_EXTERNAL_LONGDATALIST_HPP
#define BINARY_EXTERNAL_LONGDATALIST_HPP

#include <vector>

#include "binary/external/ByteViewList.hpp"
#include "binary/external/LongDataSlot.hpp"

namespace binary::external {
class LongDataList final : public ByteViewList {
public:
    LongDataList(std::vector<LongDataSlot>&& bits);
    virtual size_t Invoke(const std::span<const std::byte>& span) override;

private:
    std::vector<LongDataSlot> bits;
};
}

#endif
