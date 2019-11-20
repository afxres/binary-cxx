#pragma once

#include "../allocator_base.hpp"
#include "../allocator_helper.hpp"
#include "../converter_base.hpp"
#include "../span_view.hpp"
#include "../exceptions/throw_helper.hpp"

namespace mikodev::binary::converters
{
    /* native binary converter (copy memory directly) */
    template <typename T>
    class native_converter : public converter_base<T>
    {
    public:
        native_converter() : converter_base(sizeof(T)) {}

        virtual void encode(allocator_base& allocator, const T& item) override
        {
            allocator_helper::append(allocator, &item, sizeof(item));
        }

        virtual T decode(const span_view& span) override
        {
            if (span.size() < sizeof(T))
                exceptions::throw_helper::throw_not_enough_bytes();
            return *(reinterpret_cast<const T*>(span.data()));
        }
    };
}
