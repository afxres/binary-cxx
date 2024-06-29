#pragma once

#ifndef BINARY_ALLOCATOR_HPP
#define BINARY_ALLOCATOR_HPP

#include <cstddef>
#include <cstdint>
#include <functional>
#include <memory>
#include <span>

namespace binary {
class Allocator {
    template <typename T>
    friend class Converter;

private:
    std::shared_ptr<void> buffer;
    int32_t offset;
    int32_t bounds;
    int32_t limits;

    void Resize(int32_t length);
    void* Assign(int32_t length);
    int32_t Anchor();
    void FinishAnchor(int32_t anchor);

public:
    int32_t Length() const {
        return this->offset;
    }

    int32_t Capacity() const {
        return this->bounds;
    }

    int32_t MaxCapacity() const {
        return this->limits;
    }

    Allocator();
    Allocator(int32_t maxCapacity);
    std::span<std::byte> AsSpan();
    void Ensure(int32_t length);
    void Expand(int32_t length);
    void Append(const std::span<std::byte>& span);
    void Append(int32_t length, std::function<void(std::span<std::byte>)> action);
};
}

#endif
