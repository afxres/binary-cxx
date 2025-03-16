#ifndef BINARY_EXTERNAL_BYTEVIEWLIST_HPP
#define BINARY_EXTERNAL_BYTEVIEWLIST_HPP

#include <cstddef>
#include <span>

namespace binary::external {
class ByteViewList {
public:
    virtual ~ByteViewList() = 0;
    virtual size_t Invoke(const std::span<const std::byte>& span) = 0;
};
}

#endif
