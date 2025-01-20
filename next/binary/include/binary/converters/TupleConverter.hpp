#ifndef BINARY_CONVERTERS_TUPLECONVERTER_HPP
#define BINARY_CONVERTERS_TUPLECONVERTER_HPP

#include <memory>
#include <tuple>

#include "binary/Converter.hpp"
#include "binary/ConverterExtensions.hpp"

namespace binary::converters {
template <typename T>
class TupleConverter;

template <template <typename...> typename T, typename... E>
    requires requires { std::tuple_size<T<E...>>::value; }
class TupleConverter<T<E...>> : public Converter<T<E...>> {
private:
    using GenericArgument = T<E...>;
    using GenericArgumentConverter = std::tuple<std::shared_ptr<Converter<std::remove_cv_t<E>>>...>;

    template <size_t Index, bool IsAuto = false>
    struct Invoke {
        static void Encode(const GenericArgumentConverter& converter, Allocator& allocator, const GenericArgument& item) {
            if constexpr (Index == std::tuple_size_v<GenericArgument> - 1 && !IsAuto) {
                std::get<Index>(converter)->Encode(allocator, std::get<Index>(item));
            } else {
                std::get<Index>(converter)->EncodeAuto(allocator, std::get<Index>(item));
            }
            if constexpr (Index != std::tuple_size_v<GenericArgument> - 1) {
                Invoke<Index + 1, IsAuto>::Encode(converter, allocator, item);
            }
        }

        static auto Detach(const GenericArgumentConverter& converter, std::span<const std::byte>& span) {
            if constexpr (Index == std::tuple_size_v<GenericArgument> - 1 && !IsAuto) {
                return std::get<Index>(converter)->Decode(span);
            } else {
                return std::get<Index>(converter)->DecodeAuto(span);
            }
        }

        static auto Decode(const GenericArgumentConverter& converter, std::span<const std::byte>& span) {
            auto result = std::make_tuple(Detach(converter, span));
            if constexpr (Index != std::tuple_size_v<GenericArgument> - 1) {
                return std::tuple_cat(result, Invoke<Index + 1, IsAuto>::Decode(converter, span));
            } else {
                return result;
            }
        }
    };

    static GenericArgument Result(std::remove_cv_t<E>&&... result) {
        return {result...};
    }

    GenericArgumentConverter converter;

public:
    TupleConverter(std::shared_ptr<Converter<std::remove_cv_t<E>>>... converter)
        : Converter<GenericArgument>(GetConverterLength(std::vector<std::shared_ptr<IConverter>>({converter...}) | std::views::transform([](const auto& converter) { return converter->Length(); })))
        , converter({converter...}) {}

    virtual void Encode(Allocator& allocator, const GenericArgument& item) override {
        Invoke<0>::Encode(this->converter, allocator, item);
    }

    virtual void EncodeAuto(Allocator& allocator, const GenericArgument& item) override {
        Invoke<0, true>::Encode(this->converter, allocator, item);
    }

    virtual GenericArgument Decode(const std::span<const std::byte>& span) override {
        std::span<const std::byte> copy = span;
        return std::apply(Result, Invoke<0>::Decode(this->converter, copy));
    }

    virtual GenericArgument DecodeAuto(std::span<const std::byte>& span) override {
        return std::apply(Result, Invoke<0, true>::Decode(this->converter, span));
    }
};
}

#endif
