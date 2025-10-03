#include <boost/test/data/test_case.hpp>
#include <boost/test/unit_test.hpp>

#include <binary/Generator.hpp>
#include <binary/GeneratorExtensions.hpp>
#include <binary/converters/LittleEndianStringConverter.hpp>
#include <binary/internal/Module.hpp>

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

namespace tests::binary::internal::ModuleTests {
BOOST_AUTO_TEST_SUITE(ModuleTests)

BOOST_AUTO_TEST_CASE(CastFromNullToStringConverterTest) {
    std::string output = std::string() + "cast converter pointer error, source is null, target argument type: '" + typeid(std::string).name() + "'";
    BOOST_REQUIRE_EXCEPTION(
        ::binary::internal::GetConverter<std::string>(std::shared_ptr<::binary::IConverter>(nullptr)),
        std::invalid_argument,
        [&output](const std::invalid_argument& e) {
            BOOST_REQUIRE_EQUAL(e.what(), output);
            return true;
        });
    BOOST_REQUIRE_EXCEPTION(
        ::binary::internal::GetConverterRawPtr<std::string>(std::shared_ptr<::binary::IConverter>(nullptr)),
        std::invalid_argument,
        [&output](const std::invalid_argument& e) {
            BOOST_REQUIRE_EQUAL(e.what(), output);
            return true;
        });
}

BOOST_AUTO_TEST_CASE(CastFromStringConverterToByteConverterTest) {
    std::string output = std::string() + "cast converter pointer error, source argument type: '" + typeid(std::string).name() + "', target argument type: '" + typeid(std::byte).name() + "'";
    BOOST_REQUIRE_EXCEPTION(
        ::binary::internal::GetConverter<std::byte>(std::make_shared<::binary::converters::LittleEndianStringConverter<std::string>>()),
        std::invalid_argument,
        [&output](const std::invalid_argument& e) {
            BOOST_REQUIRE_EQUAL(e.what(), output);
            return true;
        });
    BOOST_REQUIRE_EXCEPTION(
        ::binary::internal::GetConverterRawPtr<std::byte>(std::make_shared<::binary::converters::LittleEndianStringConverter<std::string>>()),
        std::invalid_argument,
        [&output](const std::invalid_argument& e) {
            BOOST_REQUIRE_EQUAL(e.what(), output);
            return true;
        });
}

BOOST_AUTO_TEST_CASE(GetConverterUseCountTest) {
    auto source = std::make_shared<::binary::converters::LittleEndianStringConverter<std::string>>();
    BOOST_REQUIRE_EQUAL(1, source.use_count());
    ::binary::Generator generator;
    generator.AddConverter(source);
    BOOST_REQUIRE_EQUAL(2, source.use_count());
    BOOST_REQUIRE_EQUAL(2, generator.GetConverter(typeid(std::string)).use_count());
    auto actual = ::binary::GetConverter<std::string>(generator);
    BOOST_REQUIRE_EQUAL(actual.get(), source.get());
    BOOST_REQUIRE_EQUAL(3, source.use_count());
    auto borrow = ::binary::GetConverterRawPtr<std::string>(generator);
    BOOST_REQUIRE_EQUAL(actual.get(), borrow);
    BOOST_REQUIRE_EQUAL(3, source.use_count());
}

std::vector<std::tuple<std::vector<size_t>, size_t>> GetConverterLengthTestData = {
    {{0, 1}, 0},
    {{1, 2}, 3},
    {{0, INT32_MAX}, 0},
    {{1, INT32_MAX - 1}, INT32_MAX},
};

BOOST_DATA_TEST_CASE(GetConverterLengthTest, GetConverterLengthTestData, lengths, expected) {
    auto length = ::binary::internal::GetConverterLength(lengths);
    BOOST_REQUIRE_EQUAL(length, expected);
}

std::vector<std::vector<size_t>> GetConverterLengthOverflowTestData = {
    {INT32_MAX, INT32_MAX},
    {0x4000'0000, 0x4000'0000},
};

BOOST_DATA_TEST_CASE(GetConverterLengthOverflowTest, GetConverterLengthOverflowTestData, lengths) {
    BOOST_REQUIRE_EXCEPTION(
        ::binary::internal::GetConverterLength(lengths),
        std::overflow_error,
        [](const std::overflow_error& e) {
            BOOST_REQUIRE_EQUAL(e.what(), "converter length overflow");
            return true;
        });
}

BOOST_AUTO_TEST_SUITE_END()
}
