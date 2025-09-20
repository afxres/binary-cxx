#ifndef BINARY_IALLOCATOR_HPP
#define BINARY_IALLOCATOR_HPP

#include <cstddef>

namespace binary {
class IAllocator {
public:
    virtual ~IAllocator() = 0;
    virtual std::byte* Resize(size_t length) = 0;
};
}

#endif
