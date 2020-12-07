#include <boost/test/unit_test.hpp>

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

    BOOST_AUTO_TEST_CASE(simple_span_view__slice__offset__size_zero)
    {
        auto data = std::shared_ptr<byte_t[]>(new byte_t[10]);
        BOOST_REQUIRE(data != nullptr);
        auto span = mki::simple_span_view(data, 10);
        BOOST_REQUIRE(span.size() == 10);
        BOOST_REQUIRE(span.data() == &data[0]);

        auto view = span.slice(10);
        BOOST_REQUIRE(view->size() == 0);
        BOOST_REQUIRE(view->data() == nullptr);
    }

    BOOST_AUTO_TEST_CASE(simple_span_view__slice__offset_length__size_zero)
    {
        auto data = std::shared_ptr<byte_t[]>(new byte_t[10]);
        BOOST_REQUIRE(data != nullptr);
        auto span = mki::simple_span_view(data, 10);
        BOOST_REQUIRE(span.size() == 10);
        BOOST_REQUIRE(span.data() == &data[0]);

        auto view = span.slice(5, 0);
        BOOST_REQUIRE(view->size() == 0);
        BOOST_REQUIRE(view->data() == nullptr);
    }

    BOOST_AUTO_TEST_CASE(simple_span_view__slice_this__offset__size_zero)
    {
        auto data = std::shared_ptr<byte_t[]>(new byte_t[10]);
        BOOST_REQUIRE(data != nullptr);
        auto span = mki::simple_span_view(data, 10);
        BOOST_REQUIRE(span.size() == 10);
        BOOST_REQUIRE(span.data() == &data[0]);

        span.slice_this(10);
        BOOST_REQUIRE(span.size() == 0);
        BOOST_REQUIRE(span.data() == nullptr);
    }

    BOOST_AUTO_TEST_CASE(simple_span_view__slice_this__offset_length__size_zero)
    {
        auto data = std::shared_ptr<byte_t[]>(new byte_t[10]);
        BOOST_REQUIRE(data != nullptr);
        auto span = mki::simple_span_view(data, 10);
        BOOST_REQUIRE(span.size() == 10);
        BOOST_REQUIRE(span.data() == &data[0]);

        span.slice_this(5, 0);
        BOOST_REQUIRE(span.size() == 0);
        BOOST_REQUIRE(span.data() == nullptr);
    }
}
