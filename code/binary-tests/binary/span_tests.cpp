#include <boost/test/unit_test.hpp>

#include <binary/span.hpp>
#include <binary/implementations/simple_c_buffer.hpp>

namespace mk = mikodev::binary;

namespace mikodev::binary::tests::span_tests
{
    BOOST_AUTO_TEST_CASE(span__constructor__empty)
    {
        mk::span span = mk::span();
        BOOST_REQUIRE_EQUAL(span.buffer(), nullptr);
        BOOST_REQUIRE_EQUAL(span.length(), 0);
    }
}
