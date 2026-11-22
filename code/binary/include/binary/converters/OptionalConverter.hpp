#ifndef BINARY_CONVERTERS_OPTIONALCONVERTER_HPP
#define BINARY_CONVERTERS_OPTIONALCONVERTER_HPP

#include <memory>
#include <optional>
#include <type_traits>

#include "binary/Converter.hpp"
#include "binary/ConverterExtensions.hpp"
#include "binary/internal/Define.hpp"
#include "binary/internal/Exception.hpp"

namespace binary::converters {
template <typename T>
class OptionalConverter;

// `std::optional<E>` is the two-case tagged union that C# calls `Nullable<T>`
// and Rust calls `Option<T>`: a length-prefixed tag (0 = empty, 1 = value)
// followed by the value in the same mode as the entry point -- `Encode` writes
// it raw, `EncodeAuto` lets the element delimit itself.
//
// The tag is byte-identical to what `VariantConverter` writes for
// `std::variant<std::monostate, E>`, because that converter already treats
// `std::monostate` as "tag only, no payload". This class does not reuse
// `VariantConverter` for two reasons, neither of which is a wire difference:
// the variant class is constrained on `std::variant_size<V<E...>>` (which is
// ill-formed for `std::optional`) and it reaches into the variant interface
// with `item.index()`, `std::get<Index>` and `std::in_place_index<Index>`.
template <typename E>
    requires std::same_as<E, std::remove_cv_t<E>>
class OptionalConverter<std::optional<E>> : public Converter<std::optional<E>> {
private:
    using T = std::optional<E>;

    static constexpr size_t None = 0;
    static constexpr size_t Some = 1;

    std::shared_ptr<Converter<E>> converter;

public:
    explicit OptionalConverter(const std::shared_ptr<Converter<E>>& converter)
        : Converter<T>()
        , converter(converter) {}

    BINARY_DEFINE_OVERRIDE_ENCODE_METHOD(T) {
        ::binary::Encode(allocator, item.has_value() ? Some : None);
        if (item.has_value()) {
            this->converter->Encode(allocator, *item);
        }
    }

    BINARY_DEFINE_OVERRIDE_ENCODE_AUTO_METHOD(T) {
        ::binary::Encode(allocator, item.has_value() ? Some : None);
        if (item.has_value()) {
            this->converter->EncodeAuto(allocator, *item);
        }
    }

    BINARY_DEFINE_OVERRIDE_DECODE_METHOD(T) {
        auto tag = ::binary::Decode(span);
        if (tag == None) {
            return {};
        }
        if (tag != Some) {
            ::binary::internal::ThrowInvalidOptionalTag(tag);
        }
        return T(std::in_place, this->converter->Decode(span));
    }

    BINARY_DEFINE_OVERRIDE_DECODE_AUTO_METHOD(T) {
        auto tag = ::binary::Decode(span);
        if (tag == None) {
            return {};
        }
        if (tag != Some) {
            ::binary::internal::ThrowInvalidOptionalTag(tag);
        }
        return T(std::in_place, this->converter->DecodeAuto(span));
    }
};
}

#endif
