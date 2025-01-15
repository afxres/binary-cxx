#pragma once

#ifndef BINARY_CONVERTERS_COLLECTIONCONVERTER_HPP
#define BINARY_CONVERTERS_COLLECTIONCONVERTER_HPP

#include <ranges>

#include "binary/Converter.hpp"
#include "binary/converters/internals/Collection.hpp"
#include "binary/converters/internals/CollectionEmplaceFunction.hpp"
#include "binary/converters/internals/CollectionReserveFunction.hpp"

namespace binary::converters {
template <
    typename T,
    typename Emplace = internals::CollectionEmplaceFunction<T>,
    typename Reserve = internals::CollectionReserveFunction<T>>
    requires std::ranges::input_range<T>
class CollectionConverter : public Converter<T> {
public:
    CollectionConverter(std::shared_ptr<Converter<std::ranges::range_value_t<T>>> converter)
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

        T result;
        auto intent = span;
        auto converter = this->converter;
        if constexpr (Reserve::IsEnable) {
            if (converter->Length() != 0) {
                size_t capacity = internals::GetCapacity<std::ranges::range_value_t<T>>(span.size(), converter->Length());
                Reserve()(result, capacity);
            }
        }
        while (!intent.empty()) {
            Emplace()(result, converter->DecodeAuto(intent));
        }
        return result;
    }

private:
    std::shared_ptr<Converter<std::ranges::range_value_t<T>>> converter;
};
}

#endif
