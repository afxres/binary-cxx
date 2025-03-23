#include <boost/mpl/list.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/unit_test.hpp>

#include <binary/Generator.hpp>
#include <binary/GeneratorExtensions.hpp>
#include <binary/converters/ContainerConverter.hpp>
#include <binary/converters/LittleEndianConverter.hpp>
#include <binary/converters/LittleEndianStringConverter.hpp>
#include <binary/converters/TupleConverter.hpp>

#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>

namespace tests::binary::converters::ContainerConverterTests {
BOOST_AUTO_TEST_SUITE(ContainerConverterTests)

using ContainerConverterTestTypeData = boost::mpl::list<
    std::vector<int32_t>, std::vector<std::string>,
    std::list<int32_t>, std::list<std::string>,
    std::set<int32_t>, std::set<std::string>,
    std::unordered_set<int32_t>, std::unordered_set<std::string>,
    std::map<int32_t, int64_t>, std::map<int32_t, std::string>, std::map<std::string, int64_t>,
    std::unordered_map<int32_t, int64_t>, std::unordered_map<int32_t, std::string>, std::unordered_map<std::string, int64_t>>;

BOOST_AUTO_TEST_CASE_TEMPLATE(ContainerConverterLengthTest, T, ContainerConverterTestTypeData) {
    ::binary::Generator generator;
    ::binary::AddConverter<::binary::converters::LittleEndianConverter<int32_t>>(generator);
    ::binary::AddConverter<::binary::converters::LittleEndianConverter<int64_t>>(generator);
    ::binary::AddConverter<::binary::converters::LittleEndianStringConverter<std::string>>(generator);
    ::binary::AddConverter<::binary::converters::TupleConverter<std::pair<const int32_t, int64_t>>>(generator);
    ::binary::AddConverter<::binary::converters::TupleConverter<std::pair<const int32_t, std::string>>>(generator);
    ::binary::AddConverter<::binary::converters::TupleConverter<std::pair<const std::string, int64_t>>>(generator);
    ::binary::AddConverter<::binary::converters::ContainerConverter<T>>(generator);
    auto converter = ::binary::GetConverter<T>(generator);
    BOOST_REQUIRE_EQUAL(0, converter->Length());
}

BOOST_AUTO_TEST_CASE_TEMPLATE(ContainerConverterEncodeDecodeEmptyContainerTest, T, ContainerConverterTestTypeData) {
    ::binary::Generator generator;
    ::binary::AddConverter<::binary::converters::LittleEndianConverter<int32_t>>(generator);
    ::binary::AddConverter<::binary::converters::LittleEndianConverter<int64_t>>(generator);
    ::binary::AddConverter<::binary::converters::LittleEndianStringConverter<std::string>>(generator);
    ::binary::AddConverter<::binary::converters::TupleConverter<std::pair<const int32_t, int64_t>>>(generator);
    ::binary::AddConverter<::binary::converters::TupleConverter<std::pair<const int32_t, std::string>>>(generator);
    ::binary::AddConverter<::binary::converters::TupleConverter<std::pair<const std::string, int64_t>>>(generator);
    ::binary::AddConverter<::binary::converters::ContainerConverter<T>>(generator);
    auto converter = ::binary::GetConverter<T>(generator);
    T source;
    BOOST_REQUIRE_EQUAL(0, source.size());
    auto buffer = ::binary::Allocator::Invoke([&converter, &source](auto& allocator) { converter->Encode(allocator, source); });
    BOOST_REQUIRE_EQUAL(0, buffer.size());
    auto result = converter->Decode({});
    BOOST_REQUIRE_EQUAL(0, result.size());
}

BOOST_AUTO_TEST_CASE_TEMPLATE(ContainerConverterEncodeDecodeSingleDefaultValueContainerTest, T, ContainerConverterTestTypeData) {
    ::binary::Generator generator;
    ::binary::AddConverter<::binary::converters::LittleEndianConverter<int32_t>>(generator);
    ::binary::AddConverter<::binary::converters::LittleEndianConverter<int64_t>>(generator);
    ::binary::AddConverter<::binary::converters::LittleEndianStringConverter<std::string>>(generator);
    ::binary::AddConverter<::binary::converters::TupleConverter<std::pair<const int32_t, int64_t>>>(generator);
    ::binary::AddConverter<::binary::converters::TupleConverter<std::pair<const int32_t, std::string>>>(generator);
    ::binary::AddConverter<::binary::converters::TupleConverter<std::pair<const std::string, int64_t>>>(generator);
    ::binary::AddConverter<::binary::converters::ContainerConverter<T>>(generator);
    auto converter = ::binary::GetConverter<T>(generator);
    T source({std::ranges::range_value_t<T>{}});
    BOOST_REQUIRE_EQUAL(1, source.size());
    auto buffer = ::binary::Allocator::Invoke([&converter, &source](auto& allocator) { converter->Encode(allocator, source); });
    BOOST_REQUIRE_NE(0, buffer.size());
    auto result = converter->Decode(buffer);
    BOOST_REQUIRE_EQUAL(1, result.size());
}

BOOST_AUTO_TEST_SUITE_END()
}
