#include <boost/test/unit_test.hpp>

#include <binary/ConverterExtensions.hpp>
#include <binary/converters/StringConverter.hpp>

namespace tests::binary::ConverterExtensionsTests {
BOOST_AUTO_TEST_SUITE(ConverterExtensionsTests)

BOOST_AUTO_TEST_CASE(CastFromNullToStringConverterTest) {
    std::string output = std::string() + "cast converter pointer error, source is null, target argument type: '" + typeid(std::string).name() + "'";
    BOOST_REQUIRE_EXCEPTION(
        ::binary::GetConverter<std::string>(std::shared_ptr<::binary::IConverter>(nullptr)),
        std::invalid_argument,
        ([output](const std::invalid_argument& e) {
            BOOST_REQUIRE_EQUAL(e.what(), output);
            return true;
        }));
}

BOOST_AUTO_TEST_CASE(CastFromStringConverterToByteConverterTest) {
    std::string output = std::string() + "cast converter pointer error, source argument type: '" + typeid(std::string).name() + "', target argument type: '" + typeid(std::byte).name() + "'";
    BOOST_REQUIRE_EXCEPTION(
        ::binary::GetConverter<std::byte>(std::make_shared<::binary::converters::StringConverter>()),
        std::invalid_argument,
        ([output](const std::invalid_argument& e) {
            BOOST_REQUIRE_EQUAL(e.what(), output);
            return true;
        }));
}

BOOST_AUTO_TEST_SUITE_END()
}
