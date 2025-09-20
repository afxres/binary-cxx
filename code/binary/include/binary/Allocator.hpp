#ifndef BINARY_ALLOCATOR_HPP
#define BINARY_ALLOCATOR_HPP

#include <concepts>
#include <cstddef>
#include <functional>
#include <ranges>
#include <span>
#include <vector>

#include "binary/internal/TemplateResizeAllocator.hpp"

namespace binary::internal {
class AllocatorUnsafeAccessor;
}

namespace binary {
class Allocator final {
    friend class ::binary::internal::AllocatorUnsafeAccessor;

private:
    bool allocated;
    IAllocator* const bridge;
    std::byte* buffer;
    size_t offset;
    size_t bounds;
    const size_t limits;

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
    Allocator(IAllocator& allocator);
    Allocator(IAllocator& allocator, size_t maxCapacity);
    Allocator(Allocator&&) = delete;
    Allocator(const Allocator&) = delete;
    ~Allocator();
    std::span<const std::byte> AsSpan() const;
    void Ensure(size_t length);
    void Expand(size_t length);
    void Append(std::byte data);
    void Append(const std::span<const std::byte>& span);
    void Append(size_t length, const std::function<void(std::span<std::byte>)>& action);
    void Append(size_t maxLength, const std::function<void(std::span<std::byte>, size_t& bytesWritten)>& action);
    void AppendWithLengthPrefix(const std::function<void(Allocator&)>& action);
    void AppendWithLengthPrefix(size_t maxLength, const std::function<void(std::span<std::byte>, size_t& bytesWritten)>& action);

    template <std::ranges::range T = std::vector<std::byte>>
        requires std::same_as<T, std::remove_cv_t<T>> &&
        std::is_trivially_copyable_v<std::ranges::range_value_t<T>> && (sizeof(std::ranges::range_value_t<T>) == 1) &&
        requires(T& container) { container.data(); } &&
        requires(T& container, size_t length) { container.resize(length); }
    static T Invoke(const std::function<void(Allocator&)>& action) {
        T result{};
        ::binary::internal::TemplateResizeAllocator<T> bridge(result);
        Allocator allocator(bridge);
        action(allocator);
        bridge.Resize(allocator.Length());
        return result;
    }
};
}

#endif
