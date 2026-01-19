#ifndef BINARY_CONVERTERS_TUPLECONVERTER_HPP
#define BINARY_CONVERTERS_TUPLECONVERTER_HPP

#include "binary/GeneratorExtensions.hpp"
#include "binary/internal/Define.hpp"
#include "binary/internal/Module.hpp"
#include "binary/internal/TupleElement.hpp"
#include "binary/internal/TupleGetHelper.hpp"
#include "binary/internal/TupleSize.hpp"

namespace binary::converters {
template <typename T>
class TupleConverter : public Converter<T> {
private:
    template <typename Indices>
    struct ElementHelper;

    template <size_t... Index>
    struct ElementHelper<std::index_sequence<Index...>> {
        using TupleType = std::tuple<std::remove_cv_t<typename ::binary::internal::TupleElement<Index, T>::Type>...>;
        using ConverterTupleType = std::tuple<std::shared_ptr<::binary::Converter<std::remove_cv_t<typename ::binary::internal::TupleElement<Index, T>::Type>>>...>;
    };

    static constexpr size_t ElementCount = ::binary::internal::TupleSize<T>::Value;
    using ElementIndexSequence = std::make_index_sequence<ElementCount>;
    using ElementTupleType = typename ElementHelper<ElementIndexSequence>::TupleType;
    using ElementConverterTupleType = typename ElementHelper<ElementIndexSequence>::ConverterTupleType;

    template <size_t IsAuto, size_t Index>
    void EncodeInternal(Allocator& allocator, const T& item) {
        using ElementGetHelper = ::binary::internal::TupleGetHelper<Index, T>;
        const auto& converter = std::get<Index>(this->converter);
        if constexpr (IsAuto == 0 && Index == ElementCount - 1) {
            converter->Encode(allocator, ElementGetHelper::Invoke(item));
        } else {
            converter->EncodeAuto(allocator, ElementGetHelper::Invoke(item));
        }
    }

    template <size_t IsAuto, size_t... Index>
    void EncodeInternal(Allocator& allocator, const T& item, std::index_sequence<Index...>) {
        (EncodeInternal<IsAuto, Index>(allocator, item), ...);
    }

    template <size_t IsAuto, size_t Index>
    auto DecodeInternal(std::span<const std::byte>& span) {
        const auto& converter = std::get<Index>(this->converter);
        if constexpr (IsAuto == 0 && Index == ElementCount - 1) {
            return converter->Decode(span);
        } else {
            return converter->DecodeAuto(span);
        }
    }

    template <size_t IsAuto, size_t... Index>
    auto DecodeInternal(std::span<const std::byte>& span, std::index_sequence<Index...>) {
        return T{DecodeInternal<IsAuto, Index>(span)...};
    }

    static auto GetConverter(const IGenerator& generator) {
        return std::apply([&generator]<typename... E>(const E&...) { return std::tuple{::binary::GetConverter<E>(generator)...}; }, ElementTupleType());
    }

    static auto GetConverterLength(const ElementConverterTupleType& converter) {
        return std::apply([](const auto&... converter) { return ::binary::internal::GetConverterLength(std::initializer_list{converter->Length()...}); }, converter);
    }

    const ElementConverterTupleType converter;

public:
    explicit TupleConverter(const ElementConverterTupleType& converter)
        : Converter<T>(GetConverterLength(converter))
        , converter(converter) {}

    explicit TupleConverter(const IGenerator& generator)
        : TupleConverter(GetConverter(generator)) {}

    BINARY_DEFINE_OVERRIDE_ENCODE_METHOD(T) {
        EncodeInternal<0>(allocator, item, ElementIndexSequence());
    }

    BINARY_DEFINE_OVERRIDE_ENCODE_AUTO_METHOD(T) {
        EncodeInternal<1>(allocator, item, ElementIndexSequence());
    }

    BINARY_DEFINE_OVERRIDE_DECODE_METHOD(T) {
        std::span<const std::byte> copy = span;
        return DecodeInternal<0>(copy, ElementIndexSequence());
    }

    BINARY_DEFINE_OVERRIDE_DECODE_AUTO_METHOD(T) {
        return DecodeInternal<1>(span, ElementIndexSequence());
    }
};
}

#endif
