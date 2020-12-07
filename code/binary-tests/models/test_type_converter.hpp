#pragma once

#include "test_type.hpp"

#include <binary/allocator_helper.hpp>
#include <binary/converter_base.hpp>
#include <binary/exceptions/throw_helper.hpp>

namespace mikodev::binary::tests::models
{
    class test_type_converter : public converter_base<test_type>
    {
    public:
        test_type_converter() : converter_base(sizeof(size_t)) {}

        virtual void encode(allocator_base& allocator, const test_type& item) override
        {
            size_t hash = item.hash();
            allocator_helper::append(allocator, &hash, sizeof(hash));
        }

        virtual test_type decode(const span_view_base& span)
        {
            if (span.size() < sizeof(size_t))
                exceptions::throw_helper::throw_argument_exception();
            size_t hash = *(reinterpret_cast<const size_t*>(span.data()));
            return test_type(hash);
        }
    };
}
