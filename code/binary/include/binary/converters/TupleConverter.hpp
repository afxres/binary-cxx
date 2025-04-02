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
    using GenericArgument = T<E...>;
    using ElementSequence = std::make_index_sequence<sizeof...(E)>;
    static constexpr size_t AlwaysAuto = SIZE_MAX;
    static constexpr size_t NoAutoLast = sizeof...(E) - 1;

    template <size_t NoAutoIndex, size_t Index>
    void EncodeAt(Allocator& allocator, const GenericArgument& item) {
        if constexpr (Index == NoAutoIndex) {
            std::get<Index>(this->converter)->Encode(allocator, std::get<Index>(item));
        } else {
            std::get<Index>(this->converter)->EncodeAuto(allocator, std::get<Index>(item));
        }
    }

    template <size_t NoAutoIndex, size_t... Index>
    void EncodeAll(Allocator& allocator, const GenericArgument& item, std::index_sequence<Index...>) {
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
    auto DecodeAll(std::span<const std::byte>& span, std::index_sequence<Index...>) {
        return GenericArgument({DecodeAt<NoAutoIndex, Index>(span)...});
    }

    static size_t GetConverterLength(const std::shared_ptr<Converter<std::remove_cv_t<E>>>&... converter) {
        std::vector<std::shared_ptr<IConverter>> converters({converter...});
        auto lengths = converters | std::views::transform([](const auto& converter) { return converter->Length(); });
        return internal::GetConverterLength(lengths);
    }

    const std::tuple<std::shared_ptr<Converter<std::remove_cv_t<E>>>...> converter;

public:
    TupleConverter(const std::shared_ptr<Converter<std::remove_cv_t<E>>>&... converter)
        : Converter<GenericArgument>(GetConverterLength(converter...))
        , converter({converter...}) {}

    virtual void Encode(Allocator& allocator, const GenericArgument& item) override {
        EncodeAll<NoAutoLast>(allocator, item, ElementSequence());
    }

    virtual void EncodeAuto(Allocator& allocator, const GenericArgument& item) override {
        EncodeAll<AlwaysAuto>(allocator, item, ElementSequence());
    }

    virtual GenericArgument Decode(const std::span<const std::byte>& span) override {
        std::span<const std::byte> copy = span;
        return DecodeAll<NoAutoLast>(copy, ElementSequence());
    }

    virtual GenericArgument DecodeAuto(std::span<const std::byte>& span) override {
        return DecodeAll<AlwaysAuto>(span, ElementSequence());
    }
};
}

#endif
