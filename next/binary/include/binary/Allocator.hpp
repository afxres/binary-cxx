#pragma once

#ifndef BINARY_ALLOCATOR_HPP
#define BINARY_ALLOCATOR_HPP

#include <cassert>
#include <cstddef>
#include <functional>
#include <memory>
#include <span>
#include <vector>

namespace binary {
class Allocator {
    template <typename T>
    friend class Converter;

private:
    std::shared_ptr<std::byte> buffer;
    size_t offset;
    size_t bounds;
    size_t limits;

    void Resize(size_t length);
    std::byte* Assign(size_t length);
    size_t Anchor();
    void FinishAnchor(size_t anchor);

public:
    size_t Length() const { return this->offset; }
    size_t Capacity() const { return this->bounds; }
    size_t MaxCapacity() const { return this->limits; }

    Allocator();
    Allocator(size_t maxCapacity);
    std::span<const std::byte> AsSpan() const;
    void Ensure(size_t length);
    void Expand(size_t length);
    void Append(const std::span<const std::byte>& span);
    void Append(size_t length, std::function<void(std::span<std::byte>)> action);
    void AppendWithLengthPrefix(const std::span<const std::byte>& span);

    static std::vector<std::byte> Invoke(std::function<void(Allocator&)> action);
};
}

#endif
