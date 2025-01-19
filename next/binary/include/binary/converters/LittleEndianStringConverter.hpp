#ifndef BINARY_CONVERTERS_LITTLEENDIANSTRINGCONVERTER_HPP
#define BINARY_CONVERTERS_LITTLEENDIANSTRINGCONVERTER_HPP

#include "binary/Converter.hpp"
#include "binary/Endian.hpp"

namespace binary::converters {
template <typename T>
class LittleEndianStringConverter : public Converter<T> {
public:
    virtual void Encode(Allocator& allocator, const T& item) override {
        allocator.Append(std::span(reinterpret_cast<const std::byte*>(item.data()), item.size()));
    }

    virtual T Decode(const std::span<const std::byte>& span) override {
        return T(reinterpret_cast<const typename T::value_type*>(span.data()), span.size());
    }
};
}

#endif
