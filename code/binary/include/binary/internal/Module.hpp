#ifndef BINARY_INTERNAL_MODULE_HPP
#define BINARY_INTERNAL_MODULE_HPP

#include <memory>
#include <ranges>

#include "binary/Converter.hpp"
#include "binary/internal/Endian.hpp"
#include "binary/internal/Exception.hpp"

namespace binary::internal {
size_t GetCapacity(size_t byteLength, size_t itemLength, std::type_index type);

template <typename T>
    requires std::same_as<T, std::remove_cv_t<T>>
std::shared_ptr<Converter<T>> GetConverter(const std::shared_ptr<IConverter>& converter) {
    std::shared_ptr<Converter<T>> result = std::dynamic_pointer_cast<Converter<T>>(converter);
    if (result == nullptr) {
        ::binary::internal::ThrowInvalidConverterType(converter == nullptr ? typeid(nullptr) : converter->GetGenericArgument(), typeid(T));
    }
    return result;
}

template <std::ranges::range Range>
    requires std::same_as<std::ranges::range_value_t<Range>, size_t>
size_t GetConverterLength(const Range& lengths) {
    uint64_t result = 0;
    for (auto length : lengths) {
        if (length == 0) {
            return 0;
        }
        if (length > INT32_MAX || (result += length) > INT32_MAX) {
            ::binary::internal::ThrowConverterLengthOverflow();
        }
    }
    return result;
}

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
