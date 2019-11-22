#include <boost/test/data/test_case.hpp>
#include <boost/test/test_case_template.hpp>
#include <boost/mpl/list.hpp>

#include <binary/implementations/simple_allocator.hpp>
#include <binary/converters/native_converter.hpp>

namespace mikodev::binary::tests::converters::native_converter_tests
{
    namespace mkc = mikodev::binary::converters;
    namespace mki = mikodev::binary::implementations;

    using _test_types = boost::mpl::list<int8_t, int32_t, uint16_t, uint64_t>;

    BOOST_AUTO_TEST_CASE_TEMPLATE(native_converter__size, T, _test_types)
    {
        auto converter = mkc::native_converter<T>();
        BOOST_REQUIRE_EQUAL(sizeof(T), converter.size());
    }

    template <typename TArgs>
    void _test_encode_decode(TArgs source)
    {
        auto converter = mkc::native_converter<TArgs>();
        auto allocator = mki::simple_allocator();
        converter.encode(allocator, source);
        BOOST_REQUIRE_EQUAL(sizeof(TArgs), allocator.size());

        auto view = allocator.dump_as_span_view();
        auto result = converter.decode(view);
        BOOST_REQUIRE_EQUAL(source, result);
        BOOST_REQUIRE_EQUAL(sizeof(TArgs), view.size());
    }

    auto _int64_data = std::vector<int64_t>{ -65536, 0x11223344AABBCCDD, INT64_MAX, INT64_MIN };

    BOOST_DATA_TEST_CASE(native_converter__encode_decode__int64, _int64_data)
    {
        _test_encode_decode<int64_t>(sample);
    }
}
