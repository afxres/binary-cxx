#ifndef BINARY_CONVERTERS_LITTLEENDIANSTRINGCONVERTER_HPP
#define BINARY_CONVERTERS_LITTLEENDIANSTRINGCONVERTER_HPP

#include <format>

#include "binary/Converter.hpp"
#include "binary/Endian.hpp"

namespace binary::converters {
template <typename T>
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
                    EncodeLittleEndian(&target[i], source[i]);
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
            if ((span.size() % size) != 0) {
                throw std::length_error(std::format("not enough bytes for string character, byte length: {}, character type: {}", span.size(), typeid(typename T::value_type).name()));
            }
            std::remove_const_t<T> result;
            result.resize(span.size() / size);
            auto source = reinterpret_cast<const typename T::value_type*>(span.data());
            auto target = result.data();
            for (size_t i = 0; i < result.size(); i++) {
                target[i] = DecodeLittleEndian<typename T::value_type>(&source[i]);
            }
            return result;
        }
    }
};
}

#endif
