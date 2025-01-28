#include "binary/Allocator.hpp"

#include <cassert>
#include <cstring>
#include <stdexcept>

#include "binary/internal/Length.hpp"

#define ALLOCATOR_ANCHOR_SIZE (4)
#define ALLOCATOR_ANCHOR_SHRINK_LIMITS (16)
#define ALLOCATOR_CAPACITY_SEED (128)

namespace binary {
Allocator::Allocator() {
    this->buffer = nullptr;
    this->offset = 0;
    this->bounds = 0;
    this->limits = INT32_MAX;
}

Allocator::Allocator(size_t maxCapacity) {
    if (maxCapacity > INT32_MAX) {
        throw std::invalid_argument("maxCapacity > INT32_MAX");
    }
    this->buffer = nullptr;
    this->offset = 0;
    this->bounds = 0;
    this->limits = maxCapacity;
}

std::span<const std::byte> Allocator::AsSpan() const {
    return std::span<const std::byte>(this->buffer.get(), this->offset);
}

void Allocator::Resize(size_t length) {
    assert(this->limits <= INT32_MAX);
    assert(this->bounds <= INT32_MAX);
    assert(this->offset <= INT32_MAX);
    assert(this->offset <= this->bounds);
    assert(this->bounds <= this->limits);
    assert(length != 0);

    size_t offset = this->offset;
    size_t limits = this->limits;
    uint64_t amount = static_cast<uint64_t>(offset) + length;
    if (length > INT32_MAX || amount > limits) {
        throw std::length_error("maximum capacity reached");
    }
    size_t source = this->bounds;
    uint64_t cursor = static_cast<uint64_t>(source);
    if (cursor == 0) {
        cursor = ALLOCATOR_CAPACITY_SEED;
    }
    do {
        cursor *= 2;
    } while (cursor < amount);
    if (cursor > limits) {
        cursor = limits;
    }
    assert(amount <= cursor);
    assert(cursor <= this->limits);

    size_t bounds = static_cast<size_t>(cursor);
    auto target = std::make_shared<std::byte[]>(bounds);
    if (offset != 0) {
        memcpy(target.get(), this->buffer.get(), offset);
    }
    this->buffer = target;
    this->bounds = bounds;
    assert(offset <= source);
    assert(offset <= this->bounds);
}

std::byte* Allocator::Assign(size_t length) {
    assert(length != 0);
    Ensure(length);
    size_t offset = this->offset;
    this->offset = offset + length;
    return this->buffer.get() + offset;
}

size_t Allocator::Anchor() {
    Ensure(ALLOCATOR_ANCHOR_SIZE);
    size_t offset = this->offset;
    this->offset = offset + ALLOCATOR_ANCHOR_SIZE;
    return offset;
}

void Allocator::FinishAnchor(size_t anchor) {
    assert(this->bounds <= INT32_MAX);
    assert(this->offset <= this->bounds);
    size_t offset = this->offset;
    uint64_t refers = static_cast<uint64_t>(anchor) + ALLOCATOR_ANCHOR_SIZE;
    if (anchor > INT32_MAX || refers > offset) {
        throw std::logic_error("allocator has been modified unexpectedly");
    }
    size_t length = offset - static_cast<size_t>(refers);
    std::byte* target = this->buffer.get() + anchor;
    if (length <= ALLOCATOR_ANCHOR_SHRINK_LIMITS) {
        this->offset = offset - 3;
        internal::EncodeLengthPrefix(target, length, 1);
        std::memmove(target + 1, target + 4, length);
        assert(this->offset >= 1);
        assert(this->offset <= this->bounds);
    } else {
        internal::EncodeLengthPrefix(target, length, 4);
        assert(this->offset >= 4);
        assert(this->offset <= this->bounds);
    }
}

void Allocator::Ensure(size_t length) {
    assert(this->bounds <= INT32_MAX);
    assert(this->offset <= this->bounds);
    if (length > INT32_MAX || static_cast<uint64_t>(this->offset) + length > this->bounds) {
        Resize(length);
    }
    assert(this->bounds <= this->limits);
    assert(this->bounds >= this->offset + length);
}

void Allocator::Expand(size_t length) {
    Ensure(length);
    this->offset += length;
    assert(this->bounds <= INT32_MAX);
    assert(this->offset <= this->bounds);
}

void Allocator::Append(const std::span<const std::byte>& span) {
    if (span.empty()) {
        return;
    }
    memcpy(Assign(span.size()), span.data(), span.size());
}

void Allocator::Append(size_t length, std::function<void(std::span<std::byte>)> action) {
    if (length == 0) {
        return;
    }
    action(std::span<std::byte>(Assign(length), length));
}

std::vector<std::byte> Allocator::Invoke(std::function<void(Allocator&)> action) {
    Allocator allocator;
    action(allocator);
    auto span = allocator.AsSpan();
    return std::vector(span.begin(), span.end());
}
}
