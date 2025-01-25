#ifndef BINARY_INTERNAL_CONVERTER_HPP
#define BINARY_INTERNAL_CONVERTER_HPP

#include <format>
#include <memory>
#include <ranges>

#include "binary/Converter.hpp"

namespace binary::internal {
template <typename T>
    requires std::same_as<T, std::remove_cv_t<T>>
std::shared_ptr<Converter<T>> GetConverter(std::shared_ptr<IConverter> converter) {
    std::shared_ptr<Converter<T>> result = std::dynamic_pointer_cast<Converter<T>>(converter);
    if (result == nullptr) {
        std::string source = converter == nullptr ? "source is null" : std::format("source argument type: '{}'", converter->GetGenericArgument().name());
        std::string output = std::format("cast converter pointer error, {}, target argument type: '{}'", source, typeid(Converter<T>).name());
        throw std::invalid_argument(output);
    }
    return result;
}

template <std::ranges::range Range>
    requires std::same_as<std::ranges::range_value_t<Range>, size_t>
size_t GetConverterLength(const Range& converters) {
    uint64_t result = 0;
    for (auto length : converters) {
        if (length == 0) {
            return 0;
        }
        if (length > INT32_MAX || (result += length) > INT32_MAX) {
            throw std::overflow_error("converter length overflow");
        }
    }
    return result;
}
}

#endif
