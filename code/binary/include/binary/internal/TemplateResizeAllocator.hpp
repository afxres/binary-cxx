#ifndef BINARY_INTERNAL_TEMPLATERESIZEALLOCATOR_HPP
#define BINARY_INTERNAL_TEMPLATERESIZEALLOCATOR_HPP

#include <ranges>

#include "binary/IAllocator.hpp"

namespace binary::internal {
template <typename T>
class TemplateResizeAllocator;

template <std::ranges::input_range T>
class TemplateResizeAllocator<T> : public IAllocator {
private:
    T& origin;

public:
    TemplateResizeAllocator(T& container)
        : origin(container) {}

    virtual std::byte* Resize(size_t length) override {
        auto& origin = this->origin;
        origin.resize(length);
        return reinterpret_cast<std::byte*>(origin.data());
    }
};
}

#endif
