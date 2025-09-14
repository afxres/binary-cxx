#include <boost/mpl/list.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/unit_test.hpp>

#include <binary/Generator.hpp>
#include <binary/GeneratorExtensions.hpp>
#include <binary/converters/LittleEndianConverter.hpp>
#include <binary/converters/LittleEndianStringConverter.hpp>
#include <binary/converters/TupleConverter.hpp>

#include <binary/experimental/converters/LittleEndianConverter.hpp>
#include <binary/experimental/converters/LittleEndianStringConverter.hpp>
#include <binary/experimental/converters/TupleConverter.hpp>

namespace tests::binary::experimental::converters::TupleConverterTests {
BOOST_AUTO_TEST_SUITE(TupleConverterTests)

using ConstantLengthTupleConverterTestTypeData = boost::mpl::list<
    std::pair<int16_t, int32_t>,
    std::pair<int64_t, int16_t>,
    std::tuple<int32_t>,
    std::tuple<int32_t, int64_t>,
    std::tuple<int16_t, int32_t, int64_t>,
    std::pair<const int16_t, const int32_t>,
    std::tuple<const int64_t>>;

using VariableLengthTupleConverterTestTypeData = boost::mpl::list<
    std::pair<int16_t, std::string>,
    std::pair<std::string, int32_t>,
    std::tuple<std::string>,
    std::tuple<int32_t, std::string>,
    std::tuple<int32_t, std::string, int64_t>,
    std::pair<const std::string, const int16_t>,
    std::tuple<const std::string>>;

BOOST_AUTO_TEST_CASE_TEMPLATE(ConstantLengthTupleConverterTest, T, ConstantLengthTupleConverterTestTypeData) {
    using ConverterType = ::binary::experimental::Converter<T>;
    using ActualConverterType = typename ConverterType::ActualConverterType;
    std::string name = typeid(ActualConverterType).name();
    BOOST_REQUIRE(name.find("experimental") != 0);
    BOOST_REQUIRE(name.find("TupleConverter") != 0);
    BOOST_REQUIRE_NE(0, ConverterType::Length());
    BOOST_REQUIRE_NE(0, ActualConverterType::Length());
}

BOOST_AUTO_TEST_CASE_TEMPLATE(VariableLengthTupleConverterTest, T, VariableLengthTupleConverterTestTypeData) {
    using ConverterType = ::binary::experimental::Converter<T>;
    using ActualConverterType = typename ConverterType::ActualConverterType;
    std::string name = typeid(ActualConverterType).name();
    BOOST_REQUIRE(name.find("experimental") != 0);
    BOOST_REQUIRE(name.find("TupleConverter") != 0);
    BOOST_REQUIRE_EQUAL(0, ConverterType::Length());
    BOOST_REQUIRE_EQUAL(0, ActualConverterType::Length());
}

BOOST_AUTO_TEST_CASE_TEMPLATE(ConstantLengthTupleConverterEncodeDecodeBothMethodsWithDefaultTupleValueTest, T, ConstantLengthTupleConverterTestTypeData) {
    ::binary::Generator generator;
    ::binary::AddConverter<::binary::converters::LittleEndianConverter<int16_t>>(generator);
    ::binary::AddConverter<::binary::converters::LittleEndianConverter<int32_t>>(generator);
    ::binary::AddConverter<::binary::converters::LittleEndianConverter<int64_t>>(generator);
    ::binary::AddConverter<::binary::converters::TupleConverter<T>>(generator);
    auto converter = ::binary::GetConverter<T>(generator);
    auto dataBufferOrigin = ::binary::Allocator::Invoke([&converter](auto& allocator) { converter->Encode(allocator, T()); });

    using ConverterType = ::binary::experimental::Converter<T>;
    auto dataBuffer = ::binary::Allocator::Invoke([](auto& allocator) { ConverterType::Encode(allocator, T()); });
    auto autoBuffer = ::binary::Allocator::Invoke([](auto& allocator) { ConverterType::EncodeAuto(allocator, T()); });
    BOOST_REQUIRE_EQUAL(ConverterType::Length(), dataBuffer.size());
    BOOST_REQUIRE_EQUAL(ConverterType::Length(), autoBuffer.size());
    BOOST_REQUIRE_EQUAL(std::string_view(reinterpret_cast<const char*>(dataBufferOrigin.data()), dataBufferOrigin.size()), std::string_view(reinterpret_cast<const char*>(dataBuffer.data()), dataBuffer.size()));
    BOOST_REQUIRE_EQUAL(std::string_view(reinterpret_cast<const char*>(dataBufferOrigin.data()), dataBufferOrigin.size()), std::string_view(reinterpret_cast<const char*>(autoBuffer.data()), autoBuffer.size()));

    std::span<const std::byte> dataSpan(dataBuffer);
    std::span<const std::byte> autoSpan(autoBuffer);
    auto dataResult = ConverterType::Decode(dataSpan);
    auto autoResult = ConverterType::DecodeAuto(autoSpan);
    BOOST_REQUIRE(T() == dataResult);
    BOOST_REQUIRE(T() == autoResult);
    BOOST_REQUIRE_EQUAL(dataSpan.size(), ConverterType::Length());
    BOOST_REQUIRE_EQUAL(autoSpan.size(), 0);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(VariableLengthTupleConverterEncodeDecodeBothMethodsWithDefaultTupleValueTest, T, VariableLengthTupleConverterTestTypeData) {
    ::binary::Generator generator;
    ::binary::AddConverter<::binary::converters::LittleEndianConverter<int16_t>>(generator);
    ::binary::AddConverter<::binary::converters::LittleEndianConverter<int32_t>>(generator);
    ::binary::AddConverter<::binary::converters::LittleEndianConverter<int64_t>>(generator);
    ::binary::AddConverter<::binary::converters::LittleEndianStringConverter<std::string>>(generator);
    ::binary::AddConverter<::binary::converters::TupleConverter<T>>(generator);
    auto converter = ::binary::GetConverter<T>(generator);
    auto dataBufferOrigin = ::binary::Allocator::Invoke([&converter](auto& allocator) { converter->Encode(allocator, T()); });
    auto autoBufferOrigin = ::binary::Allocator::Invoke([&converter](auto& allocator) { converter->EncodeAuto(allocator, T()); });

    using ConverterType = ::binary::experimental::Converter<T>;
    auto dataBuffer = ::binary::Allocator::Invoke([](auto& allocator) { ConverterType::Encode(allocator, T()); });
    auto autoBuffer = ::binary::Allocator::Invoke([](auto& allocator) { ConverterType::EncodeAuto(allocator, T()); });
    BOOST_REQUIRE_NE(autoBuffer.size(), 0);
    BOOST_REQUIRE_LE(dataBuffer.size(), autoBuffer.size());
    BOOST_REQUIRE_EQUAL(std::string_view(reinterpret_cast<const char*>(dataBufferOrigin.data()), dataBufferOrigin.size()), std::string_view(reinterpret_cast<const char*>(dataBuffer.data()), dataBuffer.size()));
    BOOST_REQUIRE_EQUAL(std::string_view(reinterpret_cast<const char*>(autoBufferOrigin.data()), autoBufferOrigin.size()), std::string_view(reinterpret_cast<const char*>(autoBuffer.data()), autoBuffer.size()));

    std::span<const std::byte> dataSpan(dataBuffer);
    std::span<const std::byte> autoSpan(autoBuffer);
    auto dataResult = ConverterType::Decode(dataSpan);
    auto autoResult = ConverterType::DecodeAuto(autoSpan);
    BOOST_REQUIRE(T() == dataResult);
    BOOST_REQUIRE(T() == autoResult);
    BOOST_REQUIRE_EQUAL(dataSpan.size(), dataBuffer.size());
    BOOST_REQUIRE_EQUAL(autoSpan.size(), 0);
}

std::vector<std::string> StringData = {
    "",
    "Alice",
};

BOOST_DATA_TEST_CASE(TupleConverterWithStringDataTest, StringData, data) {
    ::binary::Generator generator;
    ::binary::AddConverter<::binary::converters::LittleEndianStringConverter<std::string>>(generator);
    ::binary::AddConverter<::binary::converters::TupleConverter<std::tuple<const std::string>>>(generator);
    auto converter = ::binary::GetConverter<std::tuple<const std::string>>(generator);
    std::tuple<const std::string> source(data);
    auto dataBufferOrigin = ::binary::Allocator::Invoke([&source, &converter](auto& allocator) { converter->Encode(allocator, source); });
    auto autoBufferOrigin = ::binary::Allocator::Invoke([&source, &converter](auto& allocator) { converter->EncodeAuto(allocator, source); });

    using ConverterType = ::binary::experimental::Converter<decltype(source)>;
    auto dataBuffer = ::binary::Allocator::Invoke([&source](auto& allocator) { ConverterType::Encode(allocator, source); });
    auto autoBuffer = ::binary::Allocator::Invoke([&source](auto& allocator) { ConverterType::EncodeAuto(allocator, source); });
    BOOST_REQUIRE_LT(dataBuffer.size(), autoBuffer.size());
    BOOST_REQUIRE_EQUAL(std::string_view(reinterpret_cast<const char*>(dataBufferOrigin.data()), dataBufferOrigin.size()), std::string_view(reinterpret_cast<const char*>(dataBuffer.data()), dataBuffer.size()));
    BOOST_REQUIRE_EQUAL(std::string_view(reinterpret_cast<const char*>(autoBufferOrigin.data()), autoBufferOrigin.size()), std::string_view(reinterpret_cast<const char*>(autoBuffer.data()), autoBuffer.size()));

    std::span<const std::byte> dataSpan(dataBuffer);
    std::span<const std::byte> autoSpan(autoBuffer);
    auto dataResult = ConverterType::Decode(dataSpan);
    auto autoResult = ConverterType::DecodeAuto(autoSpan);
    BOOST_REQUIRE(source == dataResult);
    BOOST_REQUIRE(source == autoResult);
    BOOST_REQUIRE_EQUAL(dataSpan.size(), dataBuffer.size());
    BOOST_REQUIRE_EQUAL(autoSpan.size(), 0);
}

BOOST_AUTO_TEST_SUITE_END()
}
