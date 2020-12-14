#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/mpl/list.hpp>

#include <binary/converters/little_endian_converter.hpp>

namespace mikodev::binary::tests::converters::little_endian_converter_tests
{
    namespace mk = mikodev::binary;
    namespace mkc = mikodev::binary::converters;

    using __test_types = boost::mpl::list<int8_t, int32_t, uint16_t, uint64_t>;

    BOOST_AUTO_TEST_CASE_TEMPLATE(little_endian_converter__length, T, __test_types)
    {
        auto converter = mkc::little_endian_converter<T>();
        BOOST_REQUIRE_EQUAL(sizeof(T), converter.length());
    }

    template <typename TArgs>
    void __test_encode_decode(TArgs source)
    {
        byte_t buffer[16] = { static_cast<byte_t>(0) };
        auto converter = mkc::little_endian_converter<TArgs>();
        auto allocator = mk::allocator(buffer, sizeof(buffer));
        converter.encode(allocator, source);
        BOOST_REQUIRE_EQUAL(sizeof(TArgs), allocator.length());

        auto span = allocator.as_span();
        auto result = converter.decode(span);
        BOOST_REQUIRE_EQUAL(source, result);
        BOOST_REQUIRE_EQUAL(sizeof(TArgs), span.length());
    }

    auto __int64_data = std::vector<int64_t>{ -65536, 0x11223344AABBCCDD };

    BOOST_DATA_TEST_CASE(little_endian_converter__encode_decode__int64, __int64_data)
    {
        __test_encode_decode<int64_t>(sample);
    }
}
