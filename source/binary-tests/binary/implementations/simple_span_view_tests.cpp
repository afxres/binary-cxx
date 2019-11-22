#include <boost/test/auto_unit_test.hpp>

#include <binary/implementations/simple_span_view.hpp>

namespace mikodev::binary::tests::implementations::simple_span_view_tests
{
    namespace mk = mikodev::binary;
    namespace mki = mk::implementations;

    BOOST_AUTO_TEST_CASE(simple_span_view__zero_size)
    {
        auto data = std::shared_ptr<byte_t[]>(new byte_t[10]);
        BOOST_REQUIRE(data != nullptr);
        auto view = mki::simple_span_view(data, 0);
        BOOST_REQUIRE(view.size() == 0);
        BOOST_REQUIRE(view.data() == nullptr);
    }

    BOOST_AUTO_TEST_CASE(simple_span_view__slice_length_zero_size)
    {
        auto data = std::shared_ptr<byte_t[]>(new byte_t[10]);
        BOOST_REQUIRE(data.get() != nullptr);
        auto span = mki::simple_span_view(data, 10);
        BOOST_REQUIRE(span.size() == 10);
        BOOST_REQUIRE(span.data() == data.get());

        auto view = span.slice(5, 0);
        BOOST_REQUIRE(view->size() == 0);
        BOOST_REQUIRE(view->data() == nullptr);
    }
}
