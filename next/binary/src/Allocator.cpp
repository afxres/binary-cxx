#include "binary/Allocator.hpp"

#include <cassert>
#include <cstdint>
#include <cstring>
#include <stdexcept>

#include "binary/internal/Exception.hpp"
#include "binary/internal/Length.hpp"

namespace binary {
constexpr size_t AllocatorAnchorSize = 4;
constexpr size_t AllocatorAnchorShrinkLimits = 16;
constexpr size_t AllocatorCapacitySeed = 128;

Allocator::Allocator()
    : Allocator({}, INT32_MAX) {}

Allocator::Allocator(std::span<std::byte> span)
    : Allocator(span, INT32_MAX) {}

Allocator::Allocator(std::span<std::byte> span, size_t maxCapacity) {
    if (maxCapacity > INT32_MAX) {
        throw std::invalid_argument("maxCapacity > INT32_MAX");
    }
    this->allocated = false;
    this->buffer = span.data();
    this->bounds = std::min(span.size(), maxCapacity);
    this->offset = 0;
    this->limits = maxCapacity;
}

Allocator::~Allocator() {
    if (this->allocated) {
        free(this->buffer);
    }
}

std::span<const std::byte> Allocator::AsSpan() const {
    return std::span<const std::byte>(this->buffer, this->offset);
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
        cursor = AllocatorCapacitySeed;
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
    auto target = static_cast<std::byte*>(malloc(bounds));
    internal::EnsureMemoryAccess(target);
    if (offset != 0) {
        memcpy(target, this->buffer, offset);
    }
    if (this->allocated) {
        free(this->buffer);
    }
    this->allocated = true;
    this->buffer = target;
    this->bounds = bounds;
    assert(offset <= source);
    assert(offset <= this->bounds);
}

size_t Allocator::Anchor() {
    Ensure(AllocatorAnchorSize);
    size_t offset = this->offset;
    this->offset = offset + AllocatorAnchorSize;
    return offset;
}

std::byte* Allocator::Assign(size_t length) {
    assert(length != 0);
    Ensure(length);
    size_t offset = this->offset;
    this->offset = offset + length;
    return this->buffer + offset;
}

std::byte* Allocator::Create(size_t length) {
    assert(length != 0);
    Ensure(length);
    size_t offset = this->offset;
    return this->buffer + offset;
}

void Allocator::FinishAnchor(size_t anchor) {
    assert(this->bounds <= INT32_MAX);
    assert(this->offset <= this->bounds);
    size_t offset = this->offset;
    uint64_t refers = static_cast<uint64_t>(anchor) + AllocatorAnchorSize;
    if (anchor > INT32_MAX || refers > offset) {
        throw std::logic_error("allocator has been modified unexpectedly");
    }
    size_t length = offset - static_cast<size_t>(refers);
    std::byte* target = this->buffer + anchor;
    if (length <= AllocatorAnchorShrinkLimits) {
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

void Allocator::FinishCreate(size_t length) {
    size_t offset = this->offset;
    assert(this->bounds <= INT32_MAX);
    assert(this->bounds >= offset);
    assert(this->bounds >= offset + length);
    this->offset = offset + length;
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

void Allocator::Append(std::byte data) {
    *Assign(sizeof(std::byte)) = data;
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

void Allocator::Append(size_t maxLength, std::function<void(std::span<std::byte>, size_t&)> action) {
    if (maxLength == 0) {
        return;
    }
    size_t actual = SIZE_MAX;
    std::byte* target = Create(maxLength);
    action(std::span<std::byte>(target, maxLength), actual);
    if (actual > maxLength) {
        internal::ThrowInvalidBytesWrittenValue();
    }
    FinishCreate(actual);
}

void Allocator::AppendWithLengthPrefix(std::function<void(Allocator&)> action) {
    size_t anchor = Anchor();
    action(*this);
    FinishAnchor(anchor);
}

void Allocator::AppendWithLengthPrefix(size_t maxLength, std::function<void(std::span<std::byte>, size_t&)> action) {
    internal::EnsureLengthPrefixLength(maxLength);
    size_t actual;
    size_t prefixLength = internal::EncodeLengthPrefixLength(maxLength);
    std::byte* target = Create(maxLength + prefixLength);
    if (maxLength == 0) {
        actual = 0;
    } else {
        actual = SIZE_MAX;
        action(std::span<std::byte>(target + prefixLength, maxLength), actual);
        if (actual > maxLength) {
            internal::ThrowInvalidBytesWrittenValue();
        }
    }
    internal::EncodeLengthPrefix(target, actual, prefixLength);
    FinishCreate(actual + prefixLength);
}

std::vector<std::byte> Allocator::Invoke(std::function<void(Allocator&)> action) {
    Allocator allocator;
    action(allocator);
    auto span = allocator.AsSpan();
    return std::vector(span.begin(), span.end());
}
}
