#pragma once

#include "../abstract_converter.hpp"
#include "../endian.hpp"
#include "../exceptions/throw_helper.hpp"

namespace mikodev::binary::converters
{
    template <typename T>
    class little_endian_converter : public abstract_converter<T>
    {
    public:
        little_endian_converter() : abstract_converter<T>::abstract_converter(sizeof(T)) {}

        virtual void encode(allocator& allocator, const T& item) override
        {
            T little = endian::ensure_little_endian<T>(item);
            const_byte_ptr buffer = reinterpret_cast<const_byte_ptr>(&little);
            allocator::append(allocator, buffer, sizeof(item));
        }

        virtual T decode(const span& span) override
        {
            if (span.length() < sizeof(T))
                exceptions::throw_helper::throw_not_enough_bytes();
            T result = *(reinterpret_cast<const T*>(span.buffer()));
            return endian::ensure_little_endian(result);
        }
    };
}
