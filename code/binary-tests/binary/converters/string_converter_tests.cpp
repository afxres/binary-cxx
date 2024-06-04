#include <boost/test/data/test_case.hpp>
#include <boost/test/unit_test.hpp>

#include <binary/converters/string_converter.hpp>
#include <binary/implementations/simple_heap_buffer.hpp>

namespace mikodev::binary::tests::converters::string_converter_tests {
namespace mk = mikodev::binary;
namespace mkc = mk::converters;
namespace mki = mk::implementations;

BOOST_AUTO_TEST_CASE(string_converter__size) {
    auto converter = mkc::string_converter();
    BOOST_REQUIRE_EQUAL(0, converter.length());
}

void _test_encode_decode_string(const std::string& source) {
    mk::abstract_buffer_ptr buffer = mki::simple_heap_buffer().create(1024);
    auto size = source.size();
    auto allocator = mk::allocator(buffer);
    auto converter = mkc::string_converter();
    converter.encode(allocator, source);
    BOOST_REQUIRE_EQUAL(size, allocator.length());

    auto view = allocator.as_span();
    auto result = converter.decode(view);
    BOOST_REQUIRE_EQUAL(source, result);
    BOOST_REQUIRE_EQUAL(size, view.length());
}

auto _string_data = std::vector<std::string>{"", "1234", "Hello, world!", "The quick brown fox ..."};

BOOST_DATA_TEST_CASE(string_converter__encode_decode, _string_data) {
    _test_encode_decode_string(sample);
}
}
