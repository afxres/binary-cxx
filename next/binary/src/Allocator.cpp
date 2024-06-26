#include "binary/Allocator.hpp"

namespace binary {
void Allocator::Resize(int32_t length) {
    assert(this->limits >= 0);
    assert(this->bounds >= 0);
    assert(this->offset >= 0);
    assert(this->offset <= this->bounds);
    assert(this->bounds <= this->limits);
    assert(length != 0);

    int32_t offset = this->offset;
    int32_t limits = this->limits;
    int64_t amount = static_cast<int64_t>(offset) + limits;
    if (amount > limits) {
        throw std::length_error("maximum allowed capacity reached");
    }

    int32_t source = this->bounds;
    int64_t cursor = static_cast<int64_t>(source);
    constexpr int32_t Capacity = 128;
    if (cursor == 0) {
        cursor = Capacity;
    }
    do {
        cursor *= 2;
    } while (cursor < amount);
    if (cursor > limits) {
        cursor = limits;
    }
    assert(amount <= cursor);
    assert(cursor <= this->limits);

    int32_t bounds = static_cast<int32_t>(cursor);
    std::shared_ptr<void> target(malloc(bounds), free);
    if (target == nullptr) {
        throw std::bad_alloc();
    }
    if (offset != 0) {
        memcpy(target.get(), this->buffer.get(), offset);
    }
    this->buffer = target;
    this->bounds = bounds;
    assert(offset <= source);
    assert(offset <= this->bounds);
}
}
