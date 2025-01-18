#include <boost/mpl/list.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/unit_test.hpp>

#include <binary/Generator.hpp>
#include <binary/GeneratorExtensions.hpp>
#include <binary/converters/LittleEndianConverter.hpp>
#include <binary/converters/StringConverter.hpp>
#include <binary/converters/TupleConverter.hpp>

namespace tests::binary::converters::TupleConverterTests {
BOOST_AUTO_TEST_SUITE(TupleConverterTests)

using ConstantLengthTupleConverterTestTypeData = boost::mpl::list<
    std::pair<int16_t, int32_t>,
    std::pair<int64_t, int16_t>,
    std::tuple<int32_t>,
    std::tuple<int32_t, int64_t>,
    std::tuple<int16_t, int32_t, int64_t>>;

using VariableLengthTupleConverterTestTypeData = boost::mpl::list<
    std::pair<int16_t, std::string>,
    std::pair<std::string, int32_t>,
    std::tuple<std::string>,
    std::tuple<int32_t, std::string>,
    std::tuple<int32_t, std::string, int64_t>>;

BOOST_AUTO_TEST_CASE_TEMPLATE(ConstantLengthTupleConverterTest, T, ConstantLengthTupleConverterTestTypeData) {
    ::binary::Generator generator;
    ::binary::AddConverter<::binary::converters::LittleEndianConverter<int16_t>>(generator);
    ::binary::AddConverter<::binary::converters::LittleEndianConverter<int32_t>>(generator);
    ::binary::AddConverter<::binary::converters::LittleEndianConverter<int64_t>>(generator);
    ::binary::AddConverter<::binary::converters::TupleConverter<T>>(generator);
    auto converter = ::binary::GetConverter<T>(generator);
    BOOST_REQUIRE_EQUAL(typeid(::binary::converters::TupleConverter<T>).name(), typeid(*converter).name());
    BOOST_REQUIRE_NE(0, converter->Length());
}

BOOST_AUTO_TEST_CASE_TEMPLATE(VariableLengthTupleConverterTest, T, VariableLengthTupleConverterTestTypeData) {
    ::binary::Generator generator;
    ::binary::AddConverter<::binary::converters::LittleEndianConverter<int16_t>>(generator);
    ::binary::AddConverter<::binary::converters::LittleEndianConverter<int32_t>>(generator);
    ::binary::AddConverter<::binary::converters::LittleEndianConverter<int64_t>>(generator);
    ::binary::AddConverter<::binary::converters::StringConverter>(generator);
    ::binary::AddConverter<::binary::converters::TupleConverter<T>>(generator);
    auto converter = ::binary::GetConverter<T>(generator);
    BOOST_REQUIRE_EQUAL(typeid(::binary::converters::TupleConverter<T>).name(), typeid(*converter).name());
    BOOST_REQUIRE_EQUAL(0, converter->Length());
}

BOOST_AUTO_TEST_CASE_TEMPLATE(ConstantLengthTupleConverterEncodeDecodeBothMethodsWithDefaultTupleValueTest, T, ConstantLengthTupleConverterTestTypeData) {
    ::binary::Generator generator;
    ::binary::AddConverter<::binary::converters::LittleEndianConverter<int16_t>>(generator);
    ::binary::AddConverter<::binary::converters::LittleEndianConverter<int32_t>>(generator);
    ::binary::AddConverter<::binary::converters::LittleEndianConverter<int64_t>>(generator);
    ::binary::AddConverter<::binary::converters::TupleConverter<T>>(generator);
    auto converter = ::binary::GetConverter<T>(generator);
    auto dataBuffer = ::binary::Allocator::Invoke([converter](auto& allocator) { converter->Encode(allocator, T()); });
    auto autoBuffer = ::binary::Allocator::Invoke([converter](auto& allocator) { converter->EncodeAuto(allocator, T()); });
    BOOST_REQUIRE_EQUAL(converter->Length(), dataBuffer.size());
    BOOST_REQUIRE_EQUAL(converter->Length(), autoBuffer.size());
    BOOST_REQUIRE_EQUAL(std::string_view(reinterpret_cast<const char*>(dataBuffer.data()), dataBuffer.size()), std::string_view(reinterpret_cast<const char*>(autoBuffer.data()), autoBuffer.size()));

    std::span<const std::byte> dataSpan(dataBuffer);
    std::span<const std::byte> autoSpan(autoBuffer);
    auto dataResult = converter->Decode(dataSpan);
    auto autoResult = converter->DecodeAuto(autoSpan);
    BOOST_REQUIRE(T() == dataResult);
    BOOST_REQUIRE(T() == autoResult);
    BOOST_REQUIRE_EQUAL(dataSpan.size(), converter->Length());
    BOOST_REQUIRE_EQUAL(autoSpan.size(), 0);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(VariableLengthTupleConverterEncodeDecodeBothMethodsWithDefaultTupleValueTest, T, VariableLengthTupleConverterTestTypeData) {
    ::binary::Generator generator;
    ::binary::AddConverter<::binary::converters::LittleEndianConverter<int16_t>>(generator);
    ::binary::AddConverter<::binary::converters::LittleEndianConverter<int32_t>>(generator);
    ::binary::AddConverter<::binary::converters::LittleEndianConverter<int64_t>>(generator);
    ::binary::AddConverter<::binary::converters::StringConverter>(generator);
    ::binary::AddConverter<::binary::converters::TupleConverter<T>>(generator);
    auto converter = ::binary::GetConverter<T>(generator);
    auto dataBuffer = ::binary::Allocator::Invoke([converter](auto& allocator) { converter->Encode(allocator, T()); });
    auto autoBuffer = ::binary::Allocator::Invoke([converter](auto& allocator) { converter->EncodeAuto(allocator, T()); });
    BOOST_REQUIRE_NE(autoBuffer.size(), 0);
    BOOST_REQUIRE_LE(dataBuffer.size(), autoBuffer.size());

    std::span<const std::byte> dataSpan(dataBuffer);
    std::span<const std::byte> autoSpan(autoBuffer);
    auto dataResult = converter->Decode(dataSpan);
    auto autoResult = converter->DecodeAuto(autoSpan);
    BOOST_REQUIRE(T() == dataResult);
    BOOST_REQUIRE(T() == autoResult);
    BOOST_REQUIRE_EQUAL(autoSpan.size(), 0);
}

BOOST_AUTO_TEST_SUITE_END()
}
