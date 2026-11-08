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
#include <span>
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

namespace {
template <typename T>
std::vector<std::byte> EncodeAutoWithLengthPrefix(const std::shared_ptr<::binary::Converter<T>>& converter, const T& source) {
    return ::binary::Allocator::Invoke([&converter, &source](auto& allocator) { converter->EncodeAuto(allocator, source); });
}

std::string ToBytes(const std::vector<std::byte>& buffer) {
    return std::string(reinterpret_cast<const char*>(buffer.data()), buffer.size());
}
}

BOOST_AUTO_TEST_CASE(ContainerConverterEncodeAutoBlittableShortLengthPrefixTest) {
    ::binary::Generator generator;
    ::binary::AddConverter<::binary::converters::LittleEndianConverter<int32_t>>(generator);
    ::binary::AddConverter<::binary::converters::ContainerConverter<std::vector<int32_t>>>(generator);
    auto converter = ::binary::GetConverter<std::vector<int32_t>>(generator);
    std::vector<int32_t> source{1, 2, 3, 4, 5};
    auto buffer = EncodeAutoWithLengthPrefix(converter, source);
    auto expected = std::string("\x14\x01\x00\x00\x00\x02\x00\x00\x00\x03\x00\x00\x00\x04\x00\x00\x00\x05\x00\x00\x00", 21);
    BOOST_REQUIRE_EQUAL(expected, ToBytes(buffer));
    std::span<const std::byte> span(buffer);
    auto result = converter->DecodeAuto(span);
    BOOST_REQUIRE_EQUAL(0, span.size());
    BOOST_REQUIRE(result == source);
}

BOOST_AUTO_TEST_CASE(ContainerConverterEncodeAutoBlittableLengthPrefixBoundaryTest) {
    ::binary::Generator generator;
    ::binary::AddConverter<::binary::converters::LittleEndianConverter<int32_t>>(generator);
    ::binary::AddConverter<::binary::converters::ContainerConverter<std::vector<int32_t>>>(generator);
    auto converter = ::binary::GetConverter<std::vector<int32_t>>(generator);
    auto sixteen = EncodeAutoWithLengthPrefix(converter, std::vector<int32_t>(4, 1));
    BOOST_REQUIRE_EQUAL(17, sixteen.size());
    BOOST_REQUIRE_EQUAL(0x10u, static_cast<unsigned>(sixteen.front()));
    auto wide = EncodeAutoWithLengthPrefix(converter, std::vector<int32_t>(32, 1));
    BOOST_REQUIRE_EQUAL(132, wide.size());
    auto expected = std::string("\x80\x00\x00\x80", 4);
    BOOST_REQUIRE_EQUAL(expected, ToBytes(std::vector<std::byte>(wide.begin(), wide.begin() + 4)));
}

BOOST_AUTO_TEST_CASE(ContainerConverterEncodeAutoNonBlittableKeepsAnchorTest) {
    ::binary::Generator generator;
    ::binary::AddConverter<::binary::converters::LittleEndianStringConverter<std::string>>(generator);
    ::binary::AddConverter<::binary::converters::ContainerConverter<std::vector<std::string>>>(generator);
    auto converter = ::binary::GetConverter<std::vector<std::string>>(generator);
    std::vector<std::string> source{"wire", "encode", "tuple", "named"};
    auto buffer = EncodeAutoWithLengthPrefix(converter, source);
    auto expected = std::string("\x80\x00\x00\x18", 4);
    for (const auto& word : source) {
        expected += static_cast<char>(word.size()) + word;
    }
    BOOST_REQUIRE_EQUAL(expected, ToBytes(buffer));
    std::span<const std::byte> span(buffer);
    auto result = converter->DecodeAuto(span);
    BOOST_REQUIRE_EQUAL(0, span.size());
    BOOST_REQUIRE(result == source);
}

BOOST_AUTO_TEST_CASE(ContainerConverterEncodeAutoNonContiguousKeepsAnchorTest) {
    ::binary::Generator generator;
    ::binary::AddConverter<::binary::converters::LittleEndianConverter<int32_t>>(generator);
    ::binary::AddConverter<::binary::converters::ContainerConverter<std::list<int32_t>>>(generator);
    auto converter = ::binary::GetConverter<std::list<int32_t>>(generator);
    std::list<int32_t> source{1, 2, 3, 4, 5};
    auto buffer = EncodeAutoWithLengthPrefix(converter, source);
    auto expected = std::string("\x80\x00\x00\x14\x01\x00\x00\x00\x02\x00\x00\x00\x03\x00\x00\x00\x04\x00\x00\x00\x05\x00\x00\x00", 24);
    BOOST_REQUIRE_EQUAL(expected, ToBytes(buffer));
}

BOOST_AUTO_TEST_CASE(ContainerConverterEncodeAutoEmptyContainerTest) {
    ::binary::Generator generator;
    ::binary::AddConverter<::binary::converters::LittleEndianConverter<int32_t>>(generator);
    ::binary::AddConverter<::binary::converters::ContainerConverter<std::vector<int32_t>>>(generator);
    ::binary::AddConverter<::binary::converters::ContainerConverter<std::list<int32_t>>>(generator);
    auto vector = ::binary::GetConverter<std::vector<int32_t>>(generator);
    auto list = ::binary::GetConverter<std::list<int32_t>>(generator);
    BOOST_REQUIRE_EQUAL(std::string("\x00", 1), ToBytes(EncodeAutoWithLengthPrefix(vector, std::vector<int32_t>{})));
    BOOST_REQUIRE_EQUAL(std::string("\x00", 1), ToBytes(EncodeAutoWithLengthPrefix(list, std::list<int32_t>{})));
}

BOOST_AUTO_TEST_SUITE_END()
}
