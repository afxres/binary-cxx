#ifndef BINARY_CONVERTERS_SHAREDPOINTERCONVERTER_HPP
#define BINARY_CONVERTERS_SHAREDPOINTERCONVERTER_HPP

#include <memory>
#include <type_traits>

#include "binary/Converter.hpp"
#include "binary/internal/Define.hpp"
#include "binary/internal/Exception.hpp"

namespace binary::converters {
template <typename T>
class SharedPointerConverter;

// The wire is the pointee: a null pointer is rejected instead of taking a tag,
// and entry points forward to the element converter explicitly, since the
// inherited ones dispatch on `Length()` and would drop an override on it.
template <typename T>
    requires std::same_as<T, std::remove_cv_t<T>>
class SharedPointerConverter<std::shared_ptr<T>> : public Converter<std::shared_ptr<T>> {
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
    explicit SharedPointerConverter(const std::shared_ptr<Converter<T>>& converter)
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

#endif
