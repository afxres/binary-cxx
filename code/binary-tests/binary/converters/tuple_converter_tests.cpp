#include "../../models/test_type.hpp"
#include "../../models/test_type_converter.hpp"

#include <boost/test/unit_test.hpp>

#include <binary/converters/little_endian_converter.hpp>
#include <binary/converters/string_converter.hpp>
#include <binary/converters/tuple_converter.hpp>
#include <binary/generator.hpp>
#include <binary/implementations/simple_heap_buffer.hpp>

namespace mikodev::binary::tests::converters::tuple_converter_tests {
namespace mk = mikodev::binary;
namespace mkc = mk::converters;
namespace mki = mk::implementations;

BOOST_AUTO_TEST_CASE(tuple_converter__encode_decode_3) {
    auto generator = mk::generator();
    generator.add<models::test_type_converter>();
    generator.add<mkc::tuple_converter, models::test_type, models::test_type, models::test_type>();
    auto converter = generator.get<std::tuple<models::test_type, models::test_type, models::test_type>>();
    auto source = std::make_tuple(models::test_type(2), models::test_type(3), models::test_type(4));
    auto buffer = mki::simple_heap_buffer().create(1024);
    auto allocator = mk::allocator(buffer);
    converter->encode(allocator, source);
    BOOST_REQUIRE_EQUAL(24, allocator.length());

    BOOST_TEST_MESSAGE("*** ***");

    auto view = allocator.as_span();
    BOOST_REQUIRE_EQUAL(24, view.length());
    auto result = converter->decode(view);
    BOOST_REQUIRE_EQUAL(24, view.length());
    BOOST_REQUIRE_EQUAL(std::get<0>(source), std::get<0>(result));
    BOOST_REQUIRE_EQUAL(std::get<1>(source), std::get<1>(result));
    BOOST_REQUIRE_EQUAL(std::get<2>(source), std::get<2>(result));
}
}
