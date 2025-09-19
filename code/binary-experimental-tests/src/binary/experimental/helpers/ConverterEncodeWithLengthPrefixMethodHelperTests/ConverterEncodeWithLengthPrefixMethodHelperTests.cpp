#include <boost/mpl/list.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/unit_test.hpp>

#include <binary/experimental/Converter.hpp>

namespace tests::binary::experimental::helpers::ConverterEncodeWithLengthPrefixMethodHelperTests {
BOOST_AUTO_TEST_SUITE(ConverterEncodeWithLengthPrefixMethodHelperTests)

using ConverterEncodeWithLengthPrefixMethodHelperInvokeTestTypeData = boost::mpl::list<
    int32_t,
    std::string,
    std::tuple<int32_t>,
    std::variant<int16_t, std::string>,
    std::vector<int32_t>, std::list<std::string>>;

BOOST_AUTO_TEST_CASE_TEMPLATE(ConverterEncodeWithLengthPrefixMethodHelperInvokeTest, T, ConverterEncodeWithLengthPrefixMethodHelperInvokeTestTypeData) {
    using ConverterType = ::binary::experimental::Converter<T>;
    using ConverterEncodeWithLengthPrefixMethodHelper = ::binary::experimental::helpers::ConverterEncodeWithLengthPrefixMethodHelper<ConverterType>;
    auto buffer = ::binary::Allocator::Invoke([](auto& allocator) { ConverterEncodeWithLengthPrefixMethodHelper::Invoke(allocator, T{}); });
    std::span<const std::byte> span = buffer;
    auto result = ::binary::DecodeWithLengthPrefix(span);
    BOOST_REQUIRE_EQUAL(0, span.size());
    auto actual = ConverterType::Decode(result);
    BOOST_REQUIRE(actual == T{});
}

BOOST_AUTO_TEST_SUITE_END()
}
