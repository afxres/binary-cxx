#include <boost/mpl/list.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/unit_test.hpp>

#include <binary/Generator.hpp>
#include <binary/GeneratorExtensions.hpp>
#include <binary/converters/CollectionConverter.hpp>
#include <binary/converters/LittleEndianConverter.hpp>
#include <binary/converters/StringConverter.hpp>

#include <set>
#include <unordered_set>

namespace tests::binary::converters::CollectionConverterTests {
BOOST_AUTO_TEST_SUITE(CollectionConverterTests)

using CollectionConverterTestTypeData = boost::mpl::list<
    std::vector<int32_t>, std::vector<std::string>,
    std::list<int32_t>, std::list<std::string>,
    std::set<int32_t>, std::set<std::string>,
    std::unordered_set<int32_t>, std::unordered_set<std::string>>;

BOOST_AUTO_TEST_CASE_TEMPLATE(CollectionConverterLengthTest, T, CollectionConverterTestTypeData) {
    ::binary::Generator generator;
    ::binary::AddConverter<::binary::converters::LittleEndianConverter<int32_t>>(generator);
    ::binary::AddConverter<::binary::converters::StringConverter>(generator);
    ::binary::AddConverter<::binary::converters::CollectionConverter<T>, std::ranges::range_value_t<T>>(generator);
    auto converter = ::binary::GetConverter<T>(generator);
    BOOST_REQUIRE_EQUAL(0, converter->Length());
}

BOOST_AUTO_TEST_CASE_TEMPLATE(CollectionConverterEncodeDecodeEmptyCollectionTest, T, CollectionConverterTestTypeData) {
    ::binary::Generator generator;
    ::binary::AddConverter<::binary::converters::LittleEndianConverter<int32_t>>(generator);
    ::binary::AddConverter<::binary::converters::StringConverter>(generator);
    ::binary::AddConverter<::binary::converters::CollectionConverter<T>, std::ranges::range_value_t<T>>(generator);
    auto converter = ::binary::GetConverter<T>(generator);
    T source;
    BOOST_REQUIRE_EQUAL(0, source.size());
    auto buffer = ::binary::Allocator::Invoke([converter, source](auto& allocator) { converter->Encode(allocator, source); });
    BOOST_REQUIRE_EQUAL(0, buffer.size());
    auto result = converter->Decode({});
    BOOST_REQUIRE_EQUAL(0, result.size());
}

BOOST_AUTO_TEST_CASE_TEMPLATE(CollectionConverterEncodeDecodeSingleDefaultValueCollectionTest, T, CollectionConverterTestTypeData) {
    ::binary::Generator generator;
    ::binary::AddConverter<::binary::converters::LittleEndianConverter<int32_t>>(generator);
    ::binary::AddConverter<::binary::converters::StringConverter>(generator);
    ::binary::AddConverter<::binary::converters::CollectionConverter<T>, std::ranges::range_value_t<T>>(generator);
    auto converter = ::binary::GetConverter<T>(generator);
    T source{{}};
    BOOST_REQUIRE_EQUAL(1, source.size());
    auto buffer = ::binary::Allocator::Invoke([converter, source](auto& allocator) { converter->Encode(allocator, source); });
    BOOST_REQUIRE_NE(0, buffer.size());
    auto result = converter->Decode(buffer);
    BOOST_REQUIRE_EQUAL(1, result.size());
}

BOOST_AUTO_TEST_SUITE_END()
}
