#pragma once

#include "test_type.hpp"

#include <binary/abstract_converter.hpp>

namespace mikodev::binary::tests::models {
class test_type_converter : public abstract_converter<test_type> {
public:
    test_type_converter()
        : abstract_converter(sizeof(size_t)) {}

    virtual void encode(allocator& allocator, const test_type& item) override {
        size_t hash = item.hash();
        allocator::append(allocator, reinterpret_cast<const_byte_ptr>(&hash), sizeof(hash));
    }

    virtual test_type decode(const span& span) {
        if (span.length() < sizeof(size_t))
            exceptions::throw_helper::throw_argument_exception();
        size_t hash = *(reinterpret_cast<const size_t*>(span.buffer()));
        return test_type(hash);
    }
};
}
