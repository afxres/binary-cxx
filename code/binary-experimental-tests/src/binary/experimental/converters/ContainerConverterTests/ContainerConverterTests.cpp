#include <boost/mpl/list.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/unit_test.hpp>

#include <binary/experimental/Converter.hpp>

#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>

namespace tests::binary::experimental::converters::ContainerConverterTests {
BOOST_AUTO_TEST_SUITE(ContainerConverterTests)

using ContainerConverterTestTypeData = boost::mpl::list<
    std::vector<int32_t>, std::vector<std::string>,
    std::list<int32_t>, std::list<std::string>,
    std::set<int32_t>, std::set<std::string>,
    std::unordered_set<int32_t>, std::unordered_set<std::string>,
    std::map<int32_t, int64_t>, std::map<int32_t, std::string>, std::map<std::string, int64_t>,
    std::unordered_map<int32_t, int64_t>, std::unordered_map<int32_t, std::string>, std::unordered_map<std::string, int64_t>>;

BOOST_AUTO_TEST_CASE_TEMPLATE(ContainerConverterLengthTest, T, ContainerConverterTestTypeData) {
    using ConverterType = ::binary::experimental::Converter<T>;
    std::string name = typeid(ConverterType).name();
    BOOST_REQUIRE(name.find("experimental") != 0);
    BOOST_REQUIRE(name.find("ContainerConverter") != 0);
    BOOST_REQUIRE_EQUAL(0, ConverterType::Length());
}

BOOST_AUTO_TEST_CASE_TEMPLATE(ContainerConverterEncodeDecodeEmptyContainerTest, T, ContainerConverterTestTypeData) {
    using ConverterType = ::binary::experimental::Converter<T>;
    T source;
    BOOST_REQUIRE_EQUAL(0, source.size());
    auto buffer = ::binary::Allocator::Invoke([&source](auto& allocator) { ConverterType::Encode(allocator, source); });
    BOOST_REQUIRE_EQUAL(0, buffer.size());
    auto result = ConverterType::Decode({});
    BOOST_REQUIRE_EQUAL(0, result.size());
}

BOOST_AUTO_TEST_CASE_TEMPLATE(ContainerConverterEncodeDecodeSingleDefaultValueContainerTest, T, ContainerConverterTestTypeData) {
    using ConverterType = ::binary::experimental::Converter<T>;
    T source({std::ranges::range_value_t<T>{}});
    BOOST_REQUIRE_EQUAL(1, source.size());
    auto buffer = ::binary::Allocator::Invoke([&source](auto& allocator) { ConverterType::Encode(allocator, source); });
    BOOST_REQUIRE_NE(0, buffer.size());
    auto result = ConverterType::Decode(buffer);
    BOOST_REQUIRE_EQUAL(1, result.size());
}

BOOST_AUTO_TEST_SUITE_END()
}
