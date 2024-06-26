#pragma once

#ifndef BINARY_ALLOCATOR_HPP
#define BINARY_ALLOCATOR_HPP

#include <cstddef>
#include <cstdint>
#include <memory>

#include "Define.hpp"

namespace binary {
class Allocator {
    template <typename T>
    friend class Converter;

private:
    std::shared_ptr<void> buffer;
    int32_t offset;
    int32_t bounds;
    int32_t limits;

    void Resize(int32_t length) {
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

    void* Assign(int32_t length) {
        assert(length != 0);
        Ensure(length);
        int32_t offset = this->offset;
        this->offset = offset + length;
        return static_cast<std::byte*>(this->buffer.get()) + offset;
    }

    int32_t Anchor() {
        Ensure(sizeof(int32_t));
        int32_t offset = this->offset;
        this->offset = offset + sizeof(int32_t);
        return offset;
    }

    void FinishAnchor(int32_t anchor) {
        constexpr int32_t Limits = 16;
        int32_t offset = this->offset;
        int64_t result = static_cast<int64_t>(static_cast<uint32_t>(offset)) - static_cast<uint32_t>(anchor) - sizeof(int32_t);
        if (result < 0) {
            throw std::logic_error("allocator has been modified unexpectedly");
        }
        int32_t length = static_cast<int32_t>(result);
        std::byte* target = static_cast<std::byte*>(this->buffer.get()) + anchor;
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

public:
    Allocator() {
        this->buffer = nullptr;
        this->offset = 0;
        this->bounds = 0;
        this->limits = std::numeric_limits<int32_t>::max();
    }

    Allocator(int32_t maxCapacity) {
        if (maxCapacity < 0) {
            throw std::out_of_range("maxCapacity < 0");
        }
        this->buffer = nullptr;
        this->offset = 0;
        this->bounds = 0;
        this->limits = maxCapacity;
    }

    int32_t Length() const {
        return this->offset;
    }

    int32_t Capacity() const {
        return this->bounds;
    }

    int32_t MaxCapacity() const {
        return this->limits;
    }

    std::span<std::byte> AsSpan() {
        return std::span<std::byte>(static_cast<std::byte*>(this->buffer.get()), this->offset);
    }

    void Ensure(int32_t length) {
        assert(this->offset >= 0);
        assert(this->bounds >= 0);
        if (static_cast<uint64_t>(static_cast<uint32_t>(this->offset)) + static_cast<uint32_t>(length) > static_cast<uint32_t>(this->bounds)) {
            Resize(length);
        }
        assert(this->bounds <= this->limits);
        assert(this->bounds >= this->offset + length);
    }

    void Expand(int32_t length) {
        Ensure(length);
        this->offset += length;
        assert(this->offset >= 0);
        assert(this->offset <= this->bounds);
    }

    void Append(const std::span<std::byte>& span) {
        int32_t length = EnsureLength(span.size());
        if (length == 0) {
            return;
        }
        memcpy(Assign(length), span.data(), length);
    }
};
}

#endif
