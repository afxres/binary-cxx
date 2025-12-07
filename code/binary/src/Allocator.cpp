#include "binary/Allocator.hpp"

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <cstring>
#include <stdexcept>

#include "binary/internal/Exception.hpp"
#include "binary/internal/Length.hpp"

namespace binary {
constexpr size_t AllocatorAnchorSize = 4;
constexpr size_t AllocatorCapacitySeed = 256;

Allocator::Allocator()
    : Allocator({}, INT32_MAX) {}

Allocator::Allocator(std::span<std::byte> span)
    : Allocator(span, INT32_MAX) {}

Allocator::Allocator(std::span<std::byte> span, size_t maxCapacity)
    : allocated(false)
    , bridge(nullptr)
    , buffer(span.data())
    , offset(0)
    , bounds(std::min(span.size(), maxCapacity))
    , limits(maxCapacity) {
    if (maxCapacity > INT32_MAX) {
        throw std::invalid_argument("maxCapacity > INT32_MAX");
    }
}

Allocator::Allocator(IAllocator& allocator)
    : Allocator(allocator, INT32_MAX) {}

Allocator::Allocator(IAllocator& allocator, size_t maxCapacity)
    : allocated(false)
    , bridge(&allocator)
    , buffer(nullptr)
    , offset(0)
    , bounds(0)
    , limits(maxCapacity) {
    if (maxCapacity > INT32_MAX) {
        throw std::invalid_argument("maxCapacity > INT32_MAX");
    }
}

Allocator::~Allocator() {
    if (this->allocated) {
        free(this->buffer);
    }
}

std::span<const std::byte> Allocator::AsSpan() const {
    return {this->buffer, this->offset};
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
    auto cursor = static_cast<uint64_t>(source);
    if (cursor == 0) {
        cursor = AllocatorCapacitySeed;
    }
    while (cursor < amount) {
        cursor *= 2;
    }
    cursor = std::min(cursor, limits);
    assert(amount <= cursor);
    assert(cursor <= this->limits);

    auto bounds = static_cast<size_t>(cursor);
    if (this->bridge == nullptr) {
        auto* target = static_cast<std::byte*>(malloc(bounds));
        ::binary::internal::EnsureMemoryAccess(target);
        if (offset != 0) {
            memcpy(target, this->buffer, offset);
        }
        if (this->allocated) {
            free(this->buffer);
        }
        this->allocated = true;
        this->buffer = target;
    } else {
        this->buffer = this->bridge->Resize(bounds);
        assert(this->buffer != nullptr);
        assert(this->allocated == false);
    }
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
    if (length == 0) {
        this->offset = offset - 3;
        ::binary::internal::EncodeLengthPrefix(target, length, 1);
        assert(this->offset >= 1);
        assert(this->offset <= this->bounds);
    } else {
        ::binary::internal::EncodeLengthPrefix(target, length, 4);
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
    if (length > INT32_MAX || static_cast<uint64_t>(this->offset) + length > this->bounds) [[unlikely]] {
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

void Allocator::Append(size_t length, const std::function<void(std::span<std::byte>)>& action) {
    if (length == 0) {
        return;
    }
    action(std::span<std::byte>(Assign(length), length));
}

void Allocator::Append(size_t maxLength, const std::function<void(std::span<std::byte>, size_t&)>& action) {
    if (maxLength == 0) {
        return;
    }
    size_t actual = SIZE_MAX;
    std::byte* target = Create(maxLength);
    action(std::span<std::byte>(target, maxLength), actual);
    if (actual > maxLength) {
        ::binary::internal::ThrowInvalidBytesWrittenValue();
    }
    FinishCreate(actual);
}

void Allocator::AppendWithLengthPrefix(const std::function<void(Allocator&)>& action) {
    size_t anchor = Anchor();
    action(*this);
    FinishAnchor(anchor);
}

void Allocator::AppendWithLengthPrefix(size_t maxLength, const std::function<void(std::span<std::byte>, size_t&)>& action) {
    ::binary::internal::EnsureLengthPrefixLength(maxLength);
    size_t actual = 0;
    size_t prefixLength = ::binary::internal::EncodeLengthPrefixLength(maxLength);
    std::byte* target = Create(maxLength + prefixLength);
    if (maxLength != 0) {
        actual = SIZE_MAX;
        action(std::span<std::byte>(target + prefixLength, maxLength), actual);
        if (actual > maxLength) {
            ::binary::internal::ThrowInvalidBytesWrittenValue();
        }
    }
    ::binary::internal::EncodeLengthPrefix(target, actual, prefixLength);
    FinishCreate(actual + prefixLength);
}
}
