#ifndef BINARY_INTERNAL_ALLOCATORUNSAFEACCESSOR_HPP
#define BINARY_INTERNAL_ALLOCATORUNSAFEACCESSOR_HPP

#include <cstddef>

namespace binary {
class Allocator;
}

namespace binary::internal {
class AllocatorUnsafeAccessor {
public:
    static std::byte* Assign(Allocator& allocator, size_t length);
    static size_t Anchor(Allocator& allocator);
    static void FinishAnchor(Allocator& allocator, size_t anchor);
};
}

#endif
