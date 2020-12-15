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
            allocator::append<const T&>(allocator, sizeof(item), item, [](byte_ptr buffer, length_t length, const T& status) { endian::encode_little_endian(buffer, status); });
        }

        virtual T decode(const span& span) override
        {
            if (span.length() < sizeof(T))
                exceptions::throw_helper::throw_not_enough_bytes();
            return endian::decode_little_endian<T>(span.buffer());
        }
    };
}
