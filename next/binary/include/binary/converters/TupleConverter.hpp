#ifndef BINARY_CONVERTERS_TUPLECONVERTER_HPP
#define BINARY_CONVERTERS_TUPLECONVERTER_HPP

#include <memory>
#include <tuple>

#include "binary/Converter.hpp"
#include "binary/internal/Converter.hpp"

namespace binary::converters {
template <typename T>
class TupleConverter;

template <template <typename...> typename T, typename... E>
    requires requires { std::tuple_size<T<E...>>::value; }
class TupleConverter<T<E...>> : public Converter<T<E...>> {
private:
    static constexpr size_t NoAutoLast = sizeof...(E) - 1;
    static constexpr size_t AlwaysAuto = SIZE_MAX;

    template <size_t NoAutoIndex, size_t Index>
    void EncodeAt(Allocator& allocator, const T<E...>& item) {
        if constexpr (Index == NoAutoIndex) {
            std::get<Index>(this->converter)->Encode(allocator, std::get<Index>(item));
        } else {
            std::get<Index>(this->converter)->EncodeAuto(allocator, std::get<Index>(item));
        }
    }

    template <size_t NoAutoIndex, size_t... Index>
    void EncodeAll(Allocator& allocator, const T<E...>& item, std::index_sequence<Index...>) {
        (EncodeAt<NoAutoIndex, Index>(allocator, item), ...);
    }

    template <size_t NoAutoIndex, size_t Index>
    auto DecodeAt(std::span<const std::byte>& span) {
        if constexpr (Index == NoAutoIndex) {
            return std::get<Index>(this->converter)->Decode(span);
        } else {
            return std::get<Index>(this->converter)->DecodeAuto(span);
        }
    }

    template <size_t NoAutoIndex, size_t... Index>
    T<E...> DecodeAll(std::span<const std::byte>& span, std::index_sequence<Index...>) {
        return {DecodeAt<NoAutoIndex, Index>(span)...};
    }

    std::tuple<std::shared_ptr<Converter<std::remove_cv_t<E>>>...> converter;

public:
    TupleConverter(std::shared_ptr<Converter<std::remove_cv_t<E>>>... converter)
        : Converter<T<E...>>(internal::GetConverterLength(std::vector<std::shared_ptr<IConverter>>({converter...}) | std::views::transform([](const auto& converter) { return converter->Length(); })))
        , converter({converter...}) {}

    virtual void Encode(Allocator& allocator, const T<E...>& item) override {
        EncodeAll<NoAutoLast>(allocator, item, std::make_index_sequence<sizeof...(E)>());
    }

    virtual void EncodeAuto(Allocator& allocator, const T<E...>& item) override {
        EncodeAll<AlwaysAuto>(allocator, item, std::make_index_sequence<sizeof...(E)>());
    }

    virtual T<E...> Decode(const std::span<const std::byte>& span) override {
        std::span<const std::byte> copy = span;
        return DecodeAll<NoAutoLast>(copy, std::make_index_sequence<sizeof...(E)>());
    }

    virtual T<E...> DecodeAuto(std::span<const std::byte>& span) override {
        return DecodeAll<AlwaysAuto>(span, std::make_index_sequence<sizeof...(E)>());
    }
};
}

#endif
