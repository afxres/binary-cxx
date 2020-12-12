#pragma once

#include "abstract_converter_interface.hpp"
#include "allocator.hpp"
#include "span.hpp"

#include <memory>

namespace mikodev::binary
{
    template <typename T>
    class abstract_converter;

    template <typename T>
    using abstract_converter_ptr = std::shared_ptr<abstract_converter<T>>;

    template <typename T>
    class abstract_converter : public abstract_converter_interface
    {
    public:
        using abstract_converter_interface::abstract_converter_interface;

        virtual void encode(allocator& allocator, const T& item) = 0;

        virtual void encode_auto(allocator& allocator, const T& item) = 0;

        virtual void encode_with_length_prefix(allocator& allocator, const T& item) = 0;

        virtual T decode(const span& span) = 0;

        virtual T decode_auto(span& span) = 0;

        virtual T decode_with_length_prefix(span& span) = 0;
    };
}
