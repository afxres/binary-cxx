#include <boost/test/data/test_case.hpp>
#include <boost/test/unit_test.hpp>

#include <binary/ConverterExtensions.hpp>
#include <binary/converters/StringConverter.hpp>

template <>
struct boost::test_tools::tt_detail::print_log_value<std::vector<size_t>> {
    void operator()(std::ostream& os, std::vector<size_t> const& value) {
        os << '{';
        for (auto x : value) {
            os << x << ' ';
        }
        os << '}';
    }
};

namespace tests::binary::ConverterExtensionsTests {
BOOST_AUTO_TEST_SUITE(ConverterExtensionsTests)

BOOST_AUTO_TEST_CASE(CastFromNullToStringConverterTest) {
    std::string output = std::string() + "cast converter pointer error, source is null, target type: '" + typeid(::binary::Converter<std::string>).name() + "'";
    BOOST_REQUIRE_EXCEPTION(
        ::binary::GetConverter<std::string>(std::shared_ptr<::binary::IConverter>(nullptr)),
        std::invalid_argument,
        ([output](const std::invalid_argument& e) {
            BOOST_REQUIRE_EQUAL(e.what(), output);
            return true;
        }));
}

BOOST_AUTO_TEST_CASE(CastFromStringConverterToByteConverterTest) {
    std::string output = std::string() + "cast converter pointer error, source type: '" + typeid(::binary::Converter<std::string>).name() + "', target type: '" + typeid(::binary::Converter<std::byte>).name() + "'";
    BOOST_REQUIRE_EXCEPTION(
        ::binary::GetConverter<std::byte>(std::make_shared<::binary::converters::StringConverter>()),
        std::invalid_argument,
        ([output](const std::invalid_argument& e) {
            BOOST_REQUIRE_EQUAL(e.what(), output);
            return true;
        }));
}

std::vector<std::tuple<std::vector<size_t>, size_t>> GetConverterLengthTestData = {
    {{0, 1}, 0},
    {{1, 2}, 3},
    {{0, INT32_MAX}, 0},
    {{1, INT32_MAX - 1}, INT32_MAX},
};

BOOST_DATA_TEST_CASE(GetConverterLengthTest, GetConverterLengthTestData, lengths, expected) {
    auto length = ::binary::GetConverterLength(lengths);
    BOOST_REQUIRE_EQUAL(length, expected);
}

std::vector<std::vector<size_t>> GetConverterLengthOverflowTestData = {
    {INT32_MAX, INT32_MAX},
    {0x4000'0000, 0x4000'0000},
};

BOOST_DATA_TEST_CASE(GetConverterLengthOverflowTest, GetConverterLengthOverflowTestData, lengths) {
    BOOST_REQUIRE_EXCEPTION(
        ::binary::GetConverterLength(lengths),
        std::overflow_error,
        ([](const std::overflow_error& e) {
            BOOST_REQUIRE_EQUAL(e.what(), "converter length overflow");
            return true;
        }));
}

BOOST_AUTO_TEST_SUITE_END()
}
