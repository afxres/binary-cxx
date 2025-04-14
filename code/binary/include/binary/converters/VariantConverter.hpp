#ifndef BINARY_CONVERTERS_VARIANTCONVERTER_HPP
#define BINARY_CONVERTERS_VARIANTCONVERTER_HPP

#include <memory>
#include <variant>

#include "binary/Converter.hpp"
#include "binary/ConverterExtensions.hpp"

namespace binary::converters {
template <typename T>
class VariantConverter;

template <template <typename...> typename T, typename... E>
    requires requires { std::variant_size<T<E...>>::value; }
class VariantConverter<T<E...>> : public Converter<T<E...>> {
private:
    using ObjectType = T<E...>;
    using EncodeFunction = std::function<void(Allocator&, const ObjectType&)>;
    using DecodeFunction = std::function<ObjectType(std::span<const std::byte>&)>;

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
        result.Decode = [converter](auto& span) { return ObjectType(std::in_place_index<Index>, converter->Decode(span)); };
        result.DecodeAuto = [converter](auto& span) { return ObjectType(std::in_place_index<Index>, converter->DecodeAuto(span)); };
        return result;
    }

    template <size_t... Index>
    static std::vector<MethodInfo> GetMethodInfoList(const std::shared_ptr<Converter<std::remove_cv_t<E>>>&... converter, std::index_sequence<Index...>) {
        std::vector<MethodInfo> result;
        (result.emplace_back(GetMethodInfo<Index>(converter)), ...);
        return result;
    }

    template <size_t IsAuto>
    void EncodeInternal(Allocator& allocator, const ObjectType& item) {
        auto header = item.index();
        const auto& record = this->record;
        if (header >= record.size()) {
            throw std::invalid_argument("invalid variant value");
        }

        ::binary::Encode(allocator, header);
        if constexpr (IsAuto == 0) {
            record.at(header).Encode(allocator, item);
        } else {
            record.at(header).EncodeAuto(allocator, item);
        }
    }

    template <size_t IsAuto>
    ObjectType DecodeInternal(std::span<const std::byte>& span) {
        auto header = ::binary::Decode(span);
        const auto& record = this->record;
        if (header >= record.size()) {
            throw std::invalid_argument("invalid variant index");
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

    virtual void Encode(Allocator& allocator, const ObjectType& item) override {
        EncodeInternal<0>(allocator, item);
    }

    virtual void EncodeAuto(Allocator& allocator, const ObjectType& item) override {
        EncodeInternal<1>(allocator, item);
    }

    virtual ObjectType Decode(const std::span<const std::byte>& span) override {
        std::span<const std::byte> copy = span;
        return DecodeInternal<0>(copy);
    }

    virtual ObjectType DecodeAuto(std::span<const std::byte>& span) override {
        return DecodeInternal<1>(span);
    }
};
}

#endif
