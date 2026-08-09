#ifndef BINARY_CONVERTERS_TUPLECONVERTER_HPP
#define BINARY_CONVERTERS_TUPLECONVERTER_HPP

#include "binary/internal/Define.hpp"
#include "binary/internal/Module.hpp"
#include "binary/internal/TupleElement.hpp"
#include "binary/internal/TupleGetHelper.hpp"
#include "binary/internal/TupleSize.hpp"

namespace binary::internal::converters {
template <typename T, typename... E>
    requires requires { ::binary::internal::TupleSize<T>::Value; }
class TupleConverter : public ::binary::Converter<T> {
private:
    static constexpr size_t ElementCount = ::binary::internal::TupleSize<T>::Value;
    using ElementIndexSequence = std::make_index_sequence<ElementCount>;

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

    std::tuple<std::shared_ptr<::binary::Converter<E>>...> converter;

public:
    explicit TupleConverter(const std::shared_ptr<::binary::Converter<E>>&... converter)
        : ::binary::Converter<T>(::binary::internal::GetConverterLength(std::initializer_list{converter->Length()...}))
        , converter({converter...}) {}

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

template <typename T, typename Indices>
struct TupleConverterHelper;

template <typename T, size_t... Index>
    requires requires { ::binary::internal::TupleSize<T>::Value; }
struct TupleConverterHelper<T, std::index_sequence<Index...>> {
    using Type = TupleConverter<T, std::remove_cv_t<typename ::binary::internal::TupleElement<Index, T>::Type>...>;
};
}

namespace binary::converters {
template <typename T>
    requires requires { ::binary::internal::TupleSize<T>::Value; }
using TupleConverter = typename ::binary::internal::converters::TupleConverterHelper<T, std::make_index_sequence<::binary::internal::TupleSize<T>::Value>>::Type;
}

#endif
