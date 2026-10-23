#ifndef BINARY_INTERNAL_STRING_HPP
#define BINARY_INTERNAL_STRING_HPP

#include "binary/Allocator.hpp"
#include "binary/internal/Endian.hpp"
#include "binary/internal/Length.hpp"

#include <type_traits>

namespace binary::internal {
template <typename T>
    requires std::same_as<T, std::remove_cv_t<T>>
void EncodeLittleEndianString(Allocator& allocator, const T& item) {
    if (item.empty()) {
        return;
    }
    using E = typename T::value_type;
    constexpr size_t size = sizeof(E);
    if constexpr (size == 1 || (std::endian::native == std::endian::little && std::is_trivially_copyable_v<E>)) {
        allocator.Append(std::span(reinterpret_cast<const std::byte*>(item.data()), size * item.size()));
    } else {
        allocator.Append(size * item.size(), [&item](std::span<std::byte> span) {
            assert(span.size() == size * item.size());
            auto target = reinterpret_cast<typename T::value_type*>(span.data());
            auto source = item.data();
            for (size_t i = 0; i < item.size(); i++) {
                ::binary::internal::EncodeLittleEndian(&target[i], source[i]);
            }
        });
    }
}

template <typename T>
    requires std::same_as<T, std::remove_cv_t<T>>
T DecodeLittleEndianString(const std::span<const std::byte>& span) {
    if (span.empty()) {
        return {};
    }
    using E = typename T::value_type;
    constexpr size_t size = sizeof(E);
    if constexpr (size == 1) {
        return T(reinterpret_cast<const E*>(span.data()), span.size());
    } else if constexpr (std::endian::native == std::endian::little && std::is_trivially_copyable_v<E>) {
        auto capacity = ::binary::internal::GetCapacity(span.size(), size, typeid(T));
        auto data = std::span<const E>(reinterpret_cast<const E*>(span.data()), capacity);
        return T(data.begin(), data.end());
    } else {
        T result{};
        auto capacity = ::binary::internal::GetCapacity(span.size(), size, typeid(T));
        result.resize(capacity);
        auto source = reinterpret_cast<const E*>(span.data());
        auto target = result.data();
        for (size_t i = 0; i < result.size(); i++) {
            target[i] = ::binary::internal::DecodeLittleEndian<E>(&source[i]);
        }
        return result;
    }
}
}

#endif
