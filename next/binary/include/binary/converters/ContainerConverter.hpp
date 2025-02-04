#ifndef BINARY_CONVERTERS_CONTAINERCONVERTER_HPP
#define BINARY_CONVERTERS_CONTAINERCONVERTER_HPP

#include <ranges>

#include "binary/Converter.hpp"
#include "binary/internal/ContainerInsertFunction.hpp"
#include "binary/internal/ContainerResizeFunction.hpp"
#include "binary/internal/Converter.hpp"

namespace binary::converters {
template <
    typename T,
    typename Emplace = internal::ContainerInsertFunction<T>,
    typename Reserve = internal::ContainerResizeFunction<T>>
    requires std::same_as<T, std::remove_cv_t<T>> && std::ranges::input_range<T>
class ContainerConverter : public Converter<T> {
private:
    std::shared_ptr<Converter<std::ranges::range_value_t<T>>> converter;

public:
    ContainerConverter(std::shared_ptr<Converter<std::ranges::range_value_t<T>>> converter)
        : converter(converter) {
    }

    virtual void Encode(Allocator& allocator, const T& item) override {
        auto converter = this->converter;
        for (const auto& i : item) {
            this->converter->EncodeAuto(allocator, i);
        }
    }

    virtual T Decode(const std::span<const std::byte>& span) override {
        if (span.empty()) {
            return {};
        }

        T result{};
        std::span<const std::byte> copy = span;
        auto converter = this->converter;
        if constexpr (Reserve::IsEnable) {
            if (converter->Length() != 0) {
                size_t capacity = internal::GetCapacity(span.size(), converter->Length(), typeid(T));
                Reserve()(result, capacity);
            }
        }
        while (!copy.empty()) {
            Emplace()(result, converter->DecodeAuto(copy));
        }
        return result;
    }
};
}

#endif
