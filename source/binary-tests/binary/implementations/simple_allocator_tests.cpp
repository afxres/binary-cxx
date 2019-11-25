#include <boost/test/auto_unit_test.hpp>

#include <binary/implementations/simple_allocator.hpp>

namespace mikodev::binary::tests::implementations::simple_allocator_tests
{
    namespace mk = mikodev::binary;
    namespace mki = mk::implementations;

    BOOST_AUTO_TEST_CASE(simple_allocator__constructor__default)
    {
        auto allocator = mki::simple_allocator();
        BOOST_REQUIRE_EQUAL(0, allocator.size());
        BOOST_REQUIRE_EQUAL(0, allocator.capacity());
        BOOST_REQUIRE_EQUAL(INT32_MAX, allocator.max_capacity());
        BOOST_REQUIRE_EQUAL(nullptr, allocator.data());
    }
}
