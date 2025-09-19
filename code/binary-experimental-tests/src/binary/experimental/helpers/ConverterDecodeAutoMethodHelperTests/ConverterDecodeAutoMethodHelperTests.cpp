#include <boost/test/unit_test.hpp>

#include <binary/experimental/Converter.hpp>

namespace tests::binary::experimental::helpers::ConverterDecodeAutoMethodHelperTests {
BOOST_AUTO_TEST_SUITE(ConverterDecodeAutoMethodHelperTests)

BOOST_AUTO_TEST_CASE(ConverterDecodeAutoMethodHelperInvokeWithNotEnoughBytesTest) {
    using ConverterType = ::binary::experimental::Converter<int64_t>;
    using ConverterDecodeAutoMethodHelper = ::binary::experimental::helpers::ConverterDecodeAutoMethodHelper<ConverterType>;
    auto message = "not enough bytes or byte sequence invalid";
    std::array<std::byte, sizeof(int64_t)> buffer;
    std::span<const std::byte> source = buffer;
    auto a = source.subspan(1);
    auto b = source.subspan(8);
    BOOST_REQUIRE_EXCEPTION(
        ConverterDecodeAutoMethodHelper::Invoke(a),
        std::length_error,
        [message](const std::length_error& e) {
            BOOST_REQUIRE_EQUAL(e.what(), message);
            return true;
        });
    BOOST_REQUIRE_EXCEPTION(
        ConverterDecodeAutoMethodHelper::Invoke(b),
        std::length_error,
        [message](const std::length_error& e) {
            BOOST_REQUIRE_EQUAL(e.what(), message);
            return true;
        });
}

BOOST_AUTO_TEST_SUITE_END()
}
