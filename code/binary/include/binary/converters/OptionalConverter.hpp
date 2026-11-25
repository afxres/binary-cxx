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

// A length-prefixed tag (0 = empty, 1 = value) followed by the value in the
// same mode as the entry point. The tag is byte-identical to what
// `VariantConverter` writes for `std::monostate`; that converter is not reused
// because its constraint is ill-formed for `std::optional` and its interface
// is variant-specific.
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

    BINARY_OVERRIDE_ENCODE_METHOD(T) {
        ::binary::Encode(allocator, item.has_value() ? Some : None);
        if (item.has_value()) {
            this->converter->Encode(allocator, *item);
        }
    }

    BINARY_OVERRIDE_ENCODE_AUTO_METHOD(T) {
        ::binary::Encode(allocator, item.has_value() ? Some : None);
        if (item.has_value()) {
            this->converter->EncodeAuto(allocator, *item);
        }
    }

    BINARY_OVERRIDE_DECODE_METHOD(T) {
        auto tag = ::binary::Decode(span);
        if (tag == None) {
            return {};
        }
        if (tag != Some) {
            ::binary::internal::ThrowInvalidOptionalTag(tag);
        }
        return T(std::in_place, this->converter->Decode(span));
    }

    BINARY_OVERRIDE_DECODE_AUTO_METHOD(T) {
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
