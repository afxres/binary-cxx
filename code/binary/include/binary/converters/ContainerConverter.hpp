#ifndef BINARY_CONVERTERS_CONTAINERCONVERTER_HPP
#define BINARY_CONVERTERS_CONTAINERCONVERTER_HPP

#include <format>
#include <ranges>

#include "binary/Converter.hpp"
#include "binary/internal/ContainerInsertFunction.hpp"
#include "binary/internal/ContainerResizeFunction.hpp"
#include "binary/internal/Converter.hpp"

namespace binary::converters {
template <typename T>
    requires std::same_as<T, std::remove_cv_t<T>> && std::ranges::input_range<T>
class ContainerConverter : public Converter<T> {
private:
    const std::shared_ptr<Converter<std::ranges::range_value_t<T>>> converter;

public:
    ContainerConverter(const std::shared_ptr<Converter<std::ranges::range_value_t<T>>>& converter)
        : converter(converter) {
    }

    virtual void Encode(Allocator& allocator, const T& item) override {
        const auto& converter = this->converter;
        for (const auto& i : item) {
            converter->EncodeAuto(allocator, i);
        }
    }

    virtual T Decode(const std::span<const std::byte>& span) override {
        if constexpr (!internal::ContainerInsertFunction<T>::IsEnable) {
            throw std::logic_error(std::format("no suitable emplace method found, type: {}", typeid(T).name()));
        } else {
            if (span.empty()) {
                return {};
            }
            T result{};
            std::span<const std::byte> copy = span;
            const auto& converter = this->converter;
            if constexpr (internal::ContainerResizeFunction<T>::IsEnable) {
                if (converter->Length() != 0) {
                    size_t capacity = internal::GetCapacity(span.size(), converter->Length(), typeid(T));
                    internal::ContainerResizeFunction<T>()(result, capacity);
                }
            }
            while (!copy.empty()) {
                internal::ContainerInsertFunction<T>()(result, converter->DecodeAuto(copy));
            }
            return result;
        }
    }
};
}

#endif
