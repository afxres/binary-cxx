#include <boost/test/unit_test.hpp>

#include <binary/converters/native_converter.hpp>

namespace mkc = mikodev::binary::converters;

BOOST_AUTO_TEST_CASE(native_converter__size_for_int32_int64)
{
    BOOST_REQUIRE_EQUAL(mkc::native_converter<int32_t>().size(), sizeof(int32_t));
    BOOST_REQUIRE_EQUAL(mkc::native_converter<int64_t>().size(), sizeof(int64_t));
}
