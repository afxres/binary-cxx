#pragma once

#include "../allocator_base.hpp"
#include "../converter_base.hpp"
#include "../span_view.hpp"
#include "../exceptions/throw_helper.hpp"

namespace mikodev::binary::converters
{
    template <typename T>
    class native_endian_binary_converter : public mikodev::binary::converter_base<T>
    {
    public:
        native_endian_binary_converter() : converter_base(sizeof(T)) {}

        virtual void encode(mikodev::binary::allocator_base& allocator, const T& item) override
        {
            std::byte* location = allocator.allocate(sizeof(T));
            *(reinterpret_cast<T*>(location)) = item;
        }

        virtual T decode(const span_view& span) override
        {
            if (span.size() < sizeof(T))
                mikodev::binary::exceptions::throw_helper::throw_not_enough_bytes();
            return *(reinterpret_cast<const T*>(span.data()));
        }
    };
}
