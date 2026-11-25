#ifndef BINARY_CONVERTERS_SMARTPOINTERCONVERTER_HPP
#define BINARY_CONVERTERS_SMARTPOINTERCONVERTER_HPP

#include <memory>
#include <type_traits>

#include "binary/Converter.hpp"
#include "binary/IConverter.hpp"
#include "binary/IGenerator.hpp"
#include "binary/internal/ConverterCreateFunction.hpp"
#include "binary/internal/Define.hpp"
#include "binary/internal/Exception.hpp"
#include "binary/internal/Module.hpp"

namespace binary::converters {
template <typename T>
class SmartPointerConverter;

// The ownership indirection is not part of the format: the wire is the pointee,
// so `std::unique_ptr<T>`, `std::shared_ptr<T>` and `T` agree byte for byte and a
// container keeps its element size.
//
// Every entry point is forwarded to the element converter explicitly. The
// inherited ones dispatch on `Length()` and would drop an override on the
// element -- the anchor of `EncodeWithLengthPrefix` widens a payload whose own
// writer already knows its width. A null pointer has no value to write and is
// rejected instead of taking a tag: a tag would make the pointer a different
// wire type from its pointee. Use `std::optional` for a value that may be absent.
template <typename T, typename D>
    requires std::same_as<T, std::remove_cv_t<T>> && (!std::is_array_v<T>) && std::is_default_constructible_v<D>
class SmartPointerConverter<std::unique_ptr<T, D>> : public Converter<std::unique_ptr<T, D>> {
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
    explicit SmartPointerConverter(const std::shared_ptr<Converter<T>>& converter)
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

template <typename T>
    requires std::same_as<T, std::remove_cv_t<T>>
class SmartPointerConverter<std::shared_ptr<T>> : public Converter<std::shared_ptr<T>> {
private:
    using P = std::shared_ptr<T>;

    std::shared_ptr<Converter<T>> converter;

    static const T& Value(const P& item) {
        if (!item) {
            ::binary::internal::ThrowNullPointer(typeid(P));
        }
        return *item;
    }

public:
    explicit SmartPointerConverter(const std::shared_ptr<Converter<T>>& converter)
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
        return std::make_shared<T>(this->converter->Decode(span));
    }

    BINARY_OVERRIDE_DECODE_AUTO_METHOD(P) {
        return std::make_shared<T>(this->converter->DecodeAuto(span));
    }

    BINARY_OVERRIDE_DECODE_WITH_LENGTH_PREFIX_METHOD(P) {
        return std::make_shared<T>(this->converter->DecodeWithLengthPrefix(span));
    }
};
}

namespace binary::internal {
// `std::unique_ptr<T, D>` carries two template arguments, so the generic rule of
// "one converter per template argument" would ask for a converter for the
// deleter as well.
template <typename T, typename D>
    requires std::same_as<T, std::remove_cv_t<T>> && (!std::is_array_v<T>) && std::is_default_constructible_v<D>
struct ConverterCreateFunction<::binary::converters::SmartPointerConverter<std::unique_ptr<T, D>>> {
    static auto Invoke(const IGenerator& generator) {
        return std::make_shared<::binary::converters::SmartPointerConverter<std::unique_ptr<T, D>>>(
            ::binary::internal::GetConverter<T>(generator.GetConverter(typeid(T)))
        );
    }
};
}

#endif
