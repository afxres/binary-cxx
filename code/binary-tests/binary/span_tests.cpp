#include <boost/test/unit_test.hpp>

#include <binary/span.hpp>

namespace mk = mikodev::binary;

namespace mikodev::binary::tests::span_tests
{
    BOOST_AUTO_TEST_CASE(span__constructor__empty)
    {
        mk::span span = mk::span();
        BOOST_REQUIRE_EQUAL(span.buffer(), nullptr);
        BOOST_REQUIRE_EQUAL(span.length(), 0);
    }

    BOOST_AUTO_TEST_CASE(span__constructor__unchecked_from_stack)
    {
        const char text[] = "Hello, world!";
        mk::span span = mk::span(reinterpret_cast<const_byte_ptr>(&text[0]), sizeof(text) - 1);
        BOOST_TEST_MESSAGE(reinterpret_cast<const char*>(span.buffer()));
        BOOST_REQUIRE_EQUAL(reinterpret_cast<const char*>(span.buffer()), &text[0]);
        BOOST_REQUIRE_EQUAL(span.length(), sizeof(text) - 1);
    }
}
