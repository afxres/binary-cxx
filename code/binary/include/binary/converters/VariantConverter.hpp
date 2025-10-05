#ifndef BINARY_CONVERTERS_VARIANTCONVERTER_HPP
#define BINARY_CONVERTERS_VARIANTCONVERTER_HPP

#include <memory>
#include <variant>

#include "binary/Converter.hpp"
#include "binary/ConverterExtensions.hpp"
#include "binary/internal/Define.hpp"
#include "binary/internal/Exception.hpp"

namespace binary::converters {
template <typename T>
class VariantConverter;

template <template <typename...> typename V, typename... E>
    requires requires { std::variant_size<V<E...>>::value; }
class VariantConverter<V<E...>> : public Converter<V<E...>> {
private:
    using T = V<E...>;
    using EncodeFunction = std::function<void(Allocator&, const T&)>;
    using DecodeFunction = std::function<T(std::span<const std::byte>&)>;

    struct MethodInfo {
        EncodeFunction Encode;
        EncodeFunction EncodeAuto;
        DecodeFunction Decode;
        DecodeFunction DecodeAuto;
    };

    template <size_t Index>
    static MethodInfo GetMethodInfo(const auto& converter) {
        MethodInfo result;
        result.Encode = [converter](auto& allocator, const auto& item) { converter->Encode(allocator, std::get<Index>(item)); };
        result.EncodeAuto = [converter](auto& allocator, const auto& item) { converter->EncodeAuto(allocator, std::get<Index>(item)); };
        result.Decode = [converter](auto& span) { return T(std::in_place_index<Index>, converter->Decode(span)); };
        result.DecodeAuto = [converter](auto& span) { return T(std::in_place_index<Index>, converter->DecodeAuto(span)); };
        return result;
    }

    template <size_t... Index>
    static std::vector<MethodInfo> GetMethodInfoList(const std::shared_ptr<Converter<std::remove_cv_t<E>>>&... converter, std::index_sequence<Index...>) {
        std::vector<MethodInfo> result;
        (result.emplace_back(GetMethodInfo<Index>(converter)), ...);
        return result;
    }

    template <size_t IsAuto>
    void EncodeInternal(Allocator& allocator, const T& item) {
        auto header = item.index();
        const auto& record = this->record;
        if (header >= record.size()) {
            ::binary::internal::ThrowInvalidVariantIndex(header);
        }

        ::binary::Encode(allocator, header);
        if constexpr (IsAuto == 0) {
            record.at(header).Encode(allocator, item);
        } else {
            record.at(header).EncodeAuto(allocator, item);
        }
    }

    template <size_t IsAuto>
    auto DecodeInternal(std::span<const std::byte>& span) {
        auto header = ::binary::Decode(span);
        const auto& record = this->record;
        if (header >= record.size()) {
            ::binary::internal::ThrowInvalidVariantIndex(header);
        }

        if constexpr (IsAuto == 0) {
            return record.at(header).Decode(span);
        } else {
            return record.at(header).DecodeAuto(span);
        }
    }

    const std::vector<MethodInfo> record;

public:
    VariantConverter(const std::shared_ptr<Converter<std::remove_cv_t<E>>>&... converter)
        : record(GetMethodInfoList(converter..., std::make_index_sequence<sizeof...(E)>())) {}

    BINARY_DEFINE_OVERRIDE_ENCODE_METHOD(T) {
        EncodeInternal<0>(allocator, item);
    }

    BINARY_DEFINE_OVERRIDE_ENCODE_AUTO_METHOD(T) {
        EncodeInternal<1>(allocator, item);
    }

    BINARY_DEFINE_OVERRIDE_DECODE_METHOD(T) {
        std::span<const std::byte> copy = span;
        return DecodeInternal<0>(copy);
    }

    BINARY_DEFINE_OVERRIDE_DECODE_AUTO_METHOD(T) {
        return DecodeInternal<1>(span);
    }
};
}

#endif
