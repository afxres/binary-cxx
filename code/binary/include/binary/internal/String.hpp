#ifndef BINARY_INTERNAL_STRING_HPP
#define BINARY_INTERNAL_STRING_HPP

#include "binary/internal/Endian.hpp"
#include "binary/internal/Module.hpp"

namespace binary::internal {
template <typename T>
    requires std::same_as<T, std::remove_cv_t<T>>
void EncodeLittleEndianString(Allocator& allocator, const T& item) {
    if (item.empty()) {
        return;
    }
    constexpr size_t size = sizeof(typename T::value_type);
    if constexpr (size == 1) {
        allocator.Append(std::span(reinterpret_cast<const std::byte*>(item.data()), item.size()));
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
    constexpr size_t size = sizeof(typename T::value_type);
    if constexpr (size == 1) {
        return T(reinterpret_cast<const typename T::value_type*>(span.data()), span.size());
    } else {
        T result{};
        auto capacity = ::binary::internal::GetCapacity(span.size(), size, typeid(T));
        result.resize(capacity);
        auto source = reinterpret_cast<const typename T::value_type*>(span.data());
        auto target = result.data();
        for (size_t i = 0; i < result.size(); i++) {
            target[i] = ::binary::internal::DecodeLittleEndian<typename T::value_type>(&source[i]);
        }
        return result;
    }
}
}

#endif
