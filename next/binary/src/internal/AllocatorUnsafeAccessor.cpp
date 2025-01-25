#include "binary/internal/AllocatorUnsafeAccessor.hpp"

#include "binary/Allocator.hpp"

namespace binary::internal {
std::byte* AllocatorUnsafeAccessor::Assign(Allocator& allocator, size_t length) {
    return allocator.Assign(length);
}

size_t AllocatorUnsafeAccessor::Anchor(Allocator& allocator) {
    return allocator.Anchor();
}

void AllocatorUnsafeAccessor::FinishAnchor(Allocator& allocator, size_t anchor) {
    allocator.FinishAnchor(anchor);
}
}
