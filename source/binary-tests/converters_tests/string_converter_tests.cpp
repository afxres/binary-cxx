#include <boost/test/auto_unit_test.hpp>
#include <boost/test/data/test_case.hpp>

#include <binary/converters/string_converter.hpp>
#include <binary/implementations/simple_allocator.hpp>

namespace mkc = mikodev::binary::converters;
namespace mki = mikodev::binary::implementations;

BOOST_AUTO_TEST_CASE(string_converter__size)
{
    auto converter = mkc::string_converter();
    BOOST_REQUIRE_EQUAL(0, converter.size());
}

void _test_encode_decode_string(const std::string& source)
{
    auto size = source.size();
    auto converter = mkc::string_converter();
    auto allocator = mki::simple_allocator();
    converter.encode(allocator, source);
    BOOST_REQUIRE_EQUAL(size, allocator.size());

    auto view = allocator.dump_as_span_view();
    auto result = converter.decode(view);
    BOOST_REQUIRE_EQUAL(source, result);
    BOOST_REQUIRE_EQUAL(size, view.size());
}

auto _string_data = std::vector<std::string>{ "", "1234", "Hello, world!", "The quick brown fox ..." };

BOOST_DATA_TEST_CASE(string_converter_encode_decode, _string_data)
{
    _test_encode_decode_string(sample);
}
