#pragma once

#ifndef BINARY_ALLOCATOR_HPP
#define BINARY_ALLOCATOR_HPP

#include <cassert>
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
    std::shared_ptr<std::byte> buffer;
    int32_t offset;
    int32_t bounds;
    int32_t limits;

    void Resize(size_t length);
    std::byte* Assign(size_t length);
    size_t Anchor();
    void FinishAnchor(size_t anchor);

public:
    size_t Length() const {
        assert(this->offset >= 0);
        return this->offset;
    }

    size_t Capacity() const {
        assert(this->bounds >= 0);
        return this->bounds;
    }

    size_t MaxCapacity() const {
        assert(this->limits >= 0);
        return this->limits;
    }

    Allocator();
    Allocator(size_t maxCapacity);
    std::span<const std::byte> AsSpan();
    void Ensure(size_t length);
    void Expand(size_t length);
    void Append(const std::span<const std::byte>& span);
    void Append(size_t length, std::function<void(std::span<std::byte>)> action);
    void AppendWithLengthPrefix(const std::span<const std::byte>& span);

    static std::vector<std::byte> Invoke(std::function<void(Allocator&)> action);
};
}

#endif
