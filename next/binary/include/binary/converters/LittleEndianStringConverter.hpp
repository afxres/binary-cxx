#ifndef BINARY_CONVERTERS_LITTLEENDIANSTRINGCONVERTER_HPP
#define BINARY_CONVERTERS_LITTLEENDIANSTRINGCONVERTER_HPP

#include <format>

#include "binary/Converter.hpp"
#include "binary/internal/Converter.hpp"
#include "binary/internal/Endian.hpp"

namespace binary::converters {
template <typename T>
    requires std::same_as<T, std::remove_cv_t<T>>
class LittleEndianStringConverter : public Converter<T> {
public:
    virtual void Encode(Allocator& allocator, const T& item) override {
        if (item.empty()) {
            return;
        }
        constexpr size_t size = sizeof(typename T::value_type);
        if constexpr (size == 1) {
            allocator.Append(std::span(reinterpret_cast<const std::byte*>(item.data()), item.size()));
        } else {
            allocator.Append(size * item.size(), [item](std::span<std::byte> span) {
                assert(span.size() == size * item.size());
                auto target = reinterpret_cast<typename T::value_type*>(span.data());
                auto source = item.data();
                for (size_t i = 0; i < item.size(); i++) {
                    internal::EncodeLittleEndian(&target[i], source[i]);
                }
            });
        }
    }

    virtual T Decode(const std::span<const std::byte>& span) override {
        if (span.empty()) {
            return {};
        }
        constexpr size_t size = sizeof(typename T::value_type);
        if constexpr (size == 1) {
            return T(reinterpret_cast<const typename T::value_type*>(span.data()), span.size());
        } else {
            T result;
            auto capacity = internal::GetCapacity(span.size(), size, typeid(T));
            result.resize(capacity);
            auto source = reinterpret_cast<const typename T::value_type*>(span.data());
            auto target = result.data();
            for (size_t i = 0; i < result.size(); i++) {
                target[i] = internal::DecodeLittleEndian<typename T::value_type>(&source[i]);
            }
            return result;
        }
    }
};
}

#endif
