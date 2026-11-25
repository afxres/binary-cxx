#ifndef BINARY_CONVERTERS_UNIQUEPOINTERCONVERTER_HPP
#define BINARY_CONVERTERS_UNIQUEPOINTERCONVERTER_HPP

#include <memory>
#include <type_traits>

#include "binary/Converter.hpp"
#include "binary/ConverterCreator.hpp"
#include "binary/IGenerator.hpp"
#include "binary/internal/Define.hpp"
#include "binary/internal/Exception.hpp"
#include "binary/internal/Module.hpp"

namespace binary::converters {
template <typename T>
class UniquePointerConverter;

// The wire is the pointee: a null pointer is rejected instead of taking a tag,
// and entry points forward to the element converter explicitly, since the
// inherited ones dispatch on `Length()` and would drop an override on it.
template <typename T, typename D>
    requires std::same_as<T, std::remove_cv_t<T>> && (!std::is_array_v<T>) && std::is_default_constructible_v<D>
class UniquePointerConverter<std::unique_ptr<T, D>> : public Converter<std::unique_ptr<T, D>> {
private:
    using P = std::unique_ptr<T, D>;

    std::shared_ptr<Converter<T>> converter;

    static const T& Value(const P& item) {
        if (!item) {
            ::binary::internal::ThrowNullPointer(typeid(P));
        }
        return *item;
    }

public:
    explicit UniquePointerConverter(const std::shared_ptr<Converter<T>>& converter)
        : Converter<P>(converter->Length())
        , converter(converter) {}

    BINARY_OVERRIDE_ENCODE_METHOD(P) {
        this->converter->Encode(allocator, Value(item));
    }

    BINARY_OVERRIDE_ENCODE_AUTO_METHOD(P) {
        this->converter->EncodeAuto(allocator, Value(item));
    }

    BINARY_OVERRIDE_ENCODE_WITH_LENGTH_PREFIX_METHOD(P) {
        this->converter->EncodeWithLengthPrefix(allocator, Value(item));
    }

    BINARY_OVERRIDE_DECODE_METHOD(P) {
        return P(new T(this->converter->Decode(span)));
    }

    BINARY_OVERRIDE_DECODE_AUTO_METHOD(P) {
        return P(new T(this->converter->DecodeAuto(span)));
    }

    BINARY_OVERRIDE_DECODE_WITH_LENGTH_PREFIX_METHOD(P) {
        return P(new T(this->converter->DecodeWithLengthPrefix(span)));
    }
};
}

namespace binary {
// The deleter is a second template argument, so the generic rule of "one
// converter per template argument" would ask for it too.
template <typename T, typename D>
    requires std::same_as<T, std::remove_cv_t<T>> && (!std::is_array_v<T>) && std::is_default_constructible_v<D>
struct ConverterCreator<::binary::converters::UniquePointerConverter<std::unique_ptr<T, D>>> {
    static auto Create(const IGenerator& generator) {
        return std::make_shared<::binary::converters::UniquePointerConverter<std::unique_ptr<T, D>>>(
            ::binary::internal::GetConverter<T>(generator.GetConverter(typeid(T)))
        );
    }
};
}

#endif
