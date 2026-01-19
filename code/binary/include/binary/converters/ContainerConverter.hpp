#ifndef BINARY_CONVERTERS_CONTAINERCONVERTER_HPP
#define BINARY_CONVERTERS_CONTAINERCONVERTER_HPP

#include <memory>

#include "binary/Converter.hpp"
#include "binary/internal/ContainerInsertFunction.hpp"
#include "binary/internal/ContainerResizeFunction.hpp"
#include "binary/internal/Define.hpp"
#include "binary/internal/Exception.hpp"
#include "binary/internal/Length.hpp"

namespace binary::converters {
template <typename T>
    requires std::same_as<T, std::remove_cv_t<T>>
class ContainerConverter : public Converter<T> {
private:
    const std::shared_ptr<Converter<std::ranges::range_value_t<T>>> converter;

public:
    explicit ContainerConverter(const std::shared_ptr<Converter<std::ranges::range_value_t<T>>>& converter)
        : converter(converter) {
    }

    BINARY_DEFINE_OVERRIDE_ENCODE_METHOD(T) {
        const auto& converter = this->converter;
        for (const auto& i : item) {
            converter->EncodeAuto(allocator, i);
        }
    }

    BINARY_DEFINE_OVERRIDE_DECODE_METHOD(T) {
        if constexpr (!::binary::internal::ContainerInsertFunction<T>::IsEnable) {
            ::binary::internal::ThrowNoSuitableEmplaceMethod(typeid(T));
        } else {
            if (span.empty()) {
                return {};
            }
            T result{};
            std::span<const std::byte> copy = span;
            const auto& converter = this->converter;
            if constexpr (::binary::internal::ContainerResizeFunction<T>::IsEnable) {
                if (converter->Length() != 0) {
                    size_t capacity = ::binary::internal::GetCapacity(span.size(), converter->Length(), typeid(T));
                    ::binary::internal::ContainerResizeFunction<T>::Invoke(result, capacity);
                }
            }
            while (!copy.empty()) {
                ::binary::internal::ContainerInsertFunction<T>::Invoke(result, converter->DecodeAuto(copy));
            }
            return result;
        }
    }
};
}

#endif
