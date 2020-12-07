#include "../../models/test_type.hpp"
#include "../../models/test_type_converter.hpp"

#include <boost/test/unit_test.hpp>

#include <binary/converters/native_converter.hpp>
#include <binary/converters/tuple_converter.hpp>
#include <binary/converters/string_converter.hpp>
#include <binary/implementations/simple_allocator.hpp>

namespace mikodev::binary::tests::converters::tuple_converter_tests
{
    namespace mkc = mikodev::binary::converters;
    namespace mki = mikodev::binary::implementations;

    BOOST_AUTO_TEST_CASE(tuple_converter__encode_decode_3)
    {
        auto underlying_converter = std::make_shared<models::test_type_converter>();
        auto converter = mkc::tuple_converter<models::test_type, models::test_type, models::test_type>(underlying_converter, underlying_converter, underlying_converter);
        auto source = std::make_tuple(models::test_type(2), models::test_type(3), models::test_type(4));
        auto allocator = mki::simple_allocator();
        converter.encode(allocator, source);
        BOOST_REQUIRE_EQUAL(24, allocator.size());

        BOOST_TEST_MESSAGE("*** ***");

        auto view = allocator.as_span_view();
        BOOST_REQUIRE_EQUAL(24, view.size());
        auto result = converter.decode(view);
        BOOST_REQUIRE_EQUAL(24, view.size());
        BOOST_REQUIRE_EQUAL(std::get<0>(source), std::get<0>(result));
        BOOST_REQUIRE_EQUAL(std::get<1>(source), std::get<1>(result));
        BOOST_REQUIRE_EQUAL(std::get<2>(source), std::get<2>(result));
    }
}
