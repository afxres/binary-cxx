#ifndef BINARY_EXTERNAL_BINARYOBJECT_HPP
#define BINARY_EXTERNAL_BINARYOBJECT_HPP

#include <cstddef>
#include <memory>
#include <span>
#include <vector>

#include "binary/external/ByteViewList.hpp"
#include "binary/external/HashCodeList.hpp"
#include "binary/external/LongDataList.hpp"

namespace binary::external {
std::unique_ptr<ByteViewList> CreateByteViewList(const std::vector<std::vector<std::byte>>& items, size_t& error);
std::unique_ptr<LongDataList> CreateLongDataList(const std::vector<std::vector<std::byte>>& items, size_t& error);
std::unique_ptr<HashCodeList> CreateHashCodeList(const std::vector<std::vector<std::byte>>& items, size_t& error);
}

#endif
