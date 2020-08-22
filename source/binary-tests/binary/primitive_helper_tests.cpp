#include <boost/test/data/test_case.hpp>
#include <boost/test/unit_test.hpp>

#include <binary/primitive_helper.hpp>
#include <binary/implementations/simple_allocator.hpp>

namespace mk = mikodev::binary;
namespace mki = mk::implementations;

namespace mikodev::binary::tests::primitive_helper_tests
{
    void _encode_decode_number_byte_size(number_t number, size_t size)
    {
        auto allocator = mki::simple_allocator();
        primitive_helper::encode_number(allocator, number);
        BOOST_REQUIRE_EQUAL(size, allocator.size());
        auto span = allocator.as_span_view();
        BOOST_REQUIRE_EQUAL(size, span.size());
        auto result = primitive_helper::decode_number(span);
        BOOST_REQUIRE_EQUAL(number, result);
        BOOST_REQUIRE_EQUAL(nullptr, span.data());
        BOOST_REQUIRE_EQUAL(0, span.size());
    }

    BOOST_AUTO_TEST_CASE(primitive_helper__encode_decode_number__one_byte)
    {
        for (number_t i = 0; i < 64; i++)
            _encode_decode_number_byte_size(i, 1);
        BOOST_TEST_MESSAGE("PASS!");
    }

    BOOST_AUTO_TEST_CASE(primitive_helper__encode_decode_number__two_bytes)
    {
        for (number_t i = 64; i < 16384; i++)
            _encode_decode_number_byte_size(i, 2);
        BOOST_TEST_MESSAGE("PASS!");
    }

    auto _number_four_bytes_data = std::vector<number_t>{ 16384, 0x8642, 0xAB'CDEF, INT32_MAX };

    BOOST_DATA_TEST_CASE(primitive_helper__encode_decode_number__four_bytes, _number_four_bytes_data)
    {
        _encode_decode_number_byte_size(sample, 4);
    }
}
