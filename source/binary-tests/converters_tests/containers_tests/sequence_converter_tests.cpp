#include <boost/test/auto_unit_test.hpp>
#include <boost/test/test_case_template.hpp>
#include <boost/mpl/list.hpp>

#include <list>
#include <deque>
#include <vector>

#include <binary/converters/containers/sequence_converter.hpp>
#include <binary/converters/native_converter.hpp>
#include <binary/converters/string_converter.hpp>

namespace mk = mikodev::binary;
namespace mkc = mk::converters;
namespace mkcc = mkc::containers;

BOOST_AUTO_TEST_CASE(sequence_converter__size)
{
    auto int32_converter = std::make_shared<mkc::native_converter<int32_t>>();
    auto string_converter = std::make_shared<mkc::string_converter>();

    auto list_int32_converter = mkcc::container_converter_t<std::list, int32_t>(int32_converter);
    auto list_string_converter = mkcc::container_converter_t<std::list, std::string>(string_converter);
    auto deque_int32_converter = mkcc::container_converter_t<std::deque, int32_t>(int32_converter);
    auto deque_string_converter = mkcc::container_converter_t<std::deque, std::string>(string_converter);
    auto vector_int32_converter = mkcc::container_converter_t<std::vector, int32_t>(int32_converter);
    auto vector_string_converter = mkcc::container_converter_t<std::vector, std::string>(string_converter);

    BOOST_REQUIRE_EQUAL(0, list_int32_converter.size());
    BOOST_REQUIRE_EQUAL(0, list_string_converter.size());
    BOOST_REQUIRE_EQUAL(0, deque_int32_converter.size());
    BOOST_REQUIRE_EQUAL(0, deque_string_converter.size());
    BOOST_REQUIRE_EQUAL(0, vector_int32_converter.size());
    BOOST_REQUIRE_EQUAL(0, vector_string_converter.size());
}
