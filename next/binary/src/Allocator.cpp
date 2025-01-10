#include "binary/Allocator.hpp"

#include <cassert>
#include <cstring>
#include <stdexcept>

#include "binary/Memory.hpp"

namespace binary {
Allocator::Allocator() {
    this->buffer = nullptr;
    this->offset = 0;
    this->bounds = 0;
    this->limits = INT32_MAX;
}

Allocator::Allocator(size_t maxCapacity) {
    if (maxCapacity > INT32_MAX) {
        throw std::out_of_range("maxCapacity > INT32_MAX");
    }
    this->buffer = nullptr;
    this->offset = 0;
    this->bounds = 0;
    this->limits = maxCapacity;
}

std::span<const std::byte> Allocator::AsSpan() {
    return std::span<const std::byte>(this->buffer.get(), this->offset);
}

void Allocator::Resize(size_t length) {
    assert(this->limits >= 0);
    assert(this->bounds >= 0);
    assert(this->offset >= 0);
    assert(this->offset <= this->bounds);
    assert(this->bounds <= this->limits);
    assert(length != 0);

    int32_t offset = this->offset;
    int32_t limits = this->limits;
    int64_t amount = static_cast<int64_t>(offset) + length;
    if (length > INT32_MAX || amount > limits) {
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
    std::shared_ptr<std::byte> target(static_cast<std::byte*>(malloc(bounds)), free);
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

std::byte* Allocator::Assign(size_t length) {
    assert(length != 0);
    Ensure(length);
    int32_t offset = this->offset;
    this->offset = offset + length;
    return this->buffer.get() + offset;
}

size_t Allocator::Anchor() {
    Ensure(sizeof(int32_t));
    int32_t offset = this->offset;
    this->offset = offset + sizeof(int32_t);
    return offset;
}

void Allocator::FinishAnchor(size_t anchor) {
    assert(this->offset >= 0);
    assert(this->offset <= this->bounds);
    constexpr int32_t Limits = 16;
    int32_t offset = this->offset;
    int64_t result = static_cast<int64_t>(offset) - anchor - sizeof(int32_t);
    if (anchor > INT32_MAX || result < 0) {
        throw std::logic_error("allocator has been modified unexpectedly");
    }
    int32_t length = static_cast<int32_t>(result);
    std::byte* target = this->buffer.get() + anchor;
    if (length <= Limits) {
        this->offset = offset - 3;
        EncodeLengthPrefix(target, length, 1);
        std::memmove(target + 1, target + 4, length);
        assert(this->offset >= 1);
        assert(this->offset <= this->bounds);
    } else {
        EncodeLengthPrefix(target, length, 4);
        assert(this->offset >= 4);
        assert(this->offset <= this->bounds);
    }
}

void Allocator::Ensure(size_t length) {
    assert(this->offset >= 0);
    assert(this->bounds >= 0);
    if (length > INT32_MAX || static_cast<uint64_t>(this->offset) + length > this->bounds) {
        Resize(length);
    }
    assert(this->bounds <= this->limits);
    assert(this->bounds >= this->offset + length);
}

void Allocator::Expand(size_t length) {
    Ensure(length);
    this->offset += length;
    assert(this->offset >= 0);
    assert(this->offset <= this->bounds);
}

void Allocator::Append(const std::span<const std::byte>& span) {
    int32_t length = EnsureLength(span.size());
    if (length == 0) {
        return;
    }
    memcpy(Assign(length), span.data(), length);
}

void Allocator::Append(size_t length, std::function<void(std::span<std::byte>)> action) {
    if (length == 0) {
        return;
    }
    action(std::span<std::byte>(Assign(length), length));
}

void Allocator::AppendWithLengthPrefix(const std::span<const std::byte>& span) {
    int32_t number = EnsureLength(span.size());
    int32_t prefixLength = EncodeLengthPrefixLength(number);
    std::byte* source = Assign(EnsureLength(span.size() + prefixLength));
    EncodeLengthPrefix(source, number, prefixLength);
    memcpy(source + prefixLength, span.data(), span.size());
}

std::vector<std::byte> Allocator::Invoke(std::function<void(Allocator&)> action) {
    Allocator allocator;
    action(allocator);
    auto span = allocator.AsSpan();
    return std::vector(span.begin(), span.end());
}
}
