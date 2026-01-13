#ifndef BINARY_INTERNAL_MODULE_HPP
#define BINARY_INTERNAL_MODULE_HPP

#include <memory>
#include <ranges>

#include "binary/Converter.hpp"
#include "binary/internal/Exception.hpp"

namespace binary::internal {
template <typename T>
    requires std::same_as<T, std::remove_cv_t<T>>
std::shared_ptr<Converter<T>> GetConverter(const std::shared_ptr<IConverter>& converter) {
    std::shared_ptr<Converter<T>> result = std::dynamic_pointer_cast<Converter<T>>(converter);
    if (result == nullptr) {
        ::binary::internal::ThrowInvalidConverterType(converter == nullptr ? typeid(nullptr) : converter->GetGenericArgument(), typeid(T));
    }
    return result;
}

template <typename T>
    requires std::same_as<T, std::remove_cv_t<T>>
Converter<T>* GetConverterRawPtr(const std::shared_ptr<IConverter>& converter) {
    auto* result = dynamic_cast<Converter<T>*>(converter.get());
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
    return static_cast<size_t>(result);
}
}

#endif
