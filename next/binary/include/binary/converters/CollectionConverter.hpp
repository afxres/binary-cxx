#ifndef BINARY_CONVERTERS_COLLECTIONCONVERTER_HPP
#define BINARY_CONVERTERS_COLLECTIONCONVERTER_HPP

#include <ranges>

#include "binary/Converter.hpp"

namespace binary::converters::internal {
template <typename T>
size_t GetCapacity(size_t byteLength, size_t itemLength) {
    assert(byteLength != 0);
    assert(itemLength != 0);
    if ((byteLength % itemLength) != 0) {
        throw std::length_error(std::format("not enough bytes for collection element, byte length: {}, element type: {}", byteLength, typeid(T).name()));
    }
    return byteLength / itemLength;
}

template <typename T>
struct CollectionEmplaceFunction;

template <std::ranges::input_range T>
    requires requires(T& collection, std::ranges::range_value_t<T>&& result) { collection.emplace(result); }
struct CollectionEmplaceFunction<T> {
    void operator()(T& collection, std::ranges::range_value_t<T>&& result) { collection.emplace(result); }
};

template <std::ranges::input_range T>
    requires requires(T& collection, std::ranges::range_value_t<T>&& result) { collection.emplace_back(result); }
struct CollectionEmplaceFunction<T> {
    void operator()(T& collection, std::ranges::range_value_t<T>&& result) { collection.emplace_back(result); }
};

template <typename T>
struct CollectionReserveFunction;

template <std::ranges::input_range T>
struct CollectionReserveFunction<T> {
    static constexpr bool IsEnable = false;
};

template <std::ranges::input_range T>
    requires requires(T& collection, size_t size) { collection.reserve(size); }
struct CollectionReserveFunction<T> {
    static constexpr bool IsEnable = true;
    void operator()(T& collection, size_t size) { collection.reserve(size); }
};
}

namespace binary::converters {
template <
    typename T,
    typename Emplace = internal::CollectionEmplaceFunction<T>,
    typename Reserve = internal::CollectionReserveFunction<T>>
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
        auto copy = span;
        auto converter = this->converter;
        if constexpr (Reserve::IsEnable) {
            if (converter->Length() != 0) {
                size_t capacity = internal::GetCapacity<std::ranges::range_value_t<T>>(span.size(), converter->Length());
                Reserve()(result, capacity);
            }
        }
        while (!copy.empty()) {
            Emplace()(result, converter->DecodeAuto(copy));
        }
        return result;
    }

private:
    std::shared_ptr<Converter<std::ranges::range_value_t<T>>> converter;
};
}

#endif
