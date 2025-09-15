#ifndef BINARY_ALLOCATOR_HPP
#define BINARY_ALLOCATOR_HPP

#include <cstddef>
#include <functional>
#include <span>
#include <vector>

namespace binary::internal {
class AllocatorUnsafeAccessor;
}

namespace binary {
class Allocator final {
    friend class ::binary::internal::AllocatorUnsafeAccessor;

private:
    bool allocated;
    std::byte* buffer;
    size_t offset;
    size_t bounds;
    size_t limits;

    void Resize(size_t length);
    size_t Anchor();
    std::byte* Assign(size_t length);
    std::byte* Create(size_t length);
    void FinishAnchor(size_t anchor);
    void FinishCreate(size_t length);

public:
    size_t Length() const { return this->offset; }
    size_t Capacity() const { return this->bounds; }
    size_t MaxCapacity() const { return this->limits; }

    Allocator();
    Allocator(std::span<std::byte> span);
    Allocator(std::span<std::byte> span, size_t maxCapacity);
    Allocator(Allocator&&) = delete;
    Allocator(const Allocator&) = delete;
    ~Allocator();
    std::span<const std::byte> AsSpan() const;
    void Ensure(size_t length);
    void Expand(size_t length);
    void Append(std::byte data);
    void Append(const std::span<const std::byte>& span);
    void Append(size_t length, std::function<void(std::span<std::byte>)> action);
    void Append(size_t maxLength, std::function<void(std::span<std::byte> span, size_t& bytesWritten)> action);
    void AppendWithLengthPrefix(std::function<void(Allocator&)> action);
    void AppendWithLengthPrefix(size_t maxLength, std::function<void(std::span<std::byte> span, size_t& bytesWritten)> action);

    static std::vector<std::byte> Invoke(std::function<void(Allocator&)> action);
};
}

#endif
