#ifndef BINARY_EXTERNAL_HASHCODELIST_HPP
#define BINARY_EXTERNAL_HASHCODELIST_HPP

#include <string_view>
#include <unordered_map>

#include "binary/external/ByteViewList.hpp"

namespace binary::external {
class HashCodeList final : public ByteViewList {
public:
    HashCodeList(std::unordered_map<std::string_view, size_t>&& record);
    size_t Invoke(const std::span<const std::byte>& span) override;

private:
    const std::unordered_map<std::string_view, size_t> record;
};
}

#endif
