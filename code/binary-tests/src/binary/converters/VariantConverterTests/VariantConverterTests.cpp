#include <boost/mpl/list.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/unit_test.hpp>

#include <binary/Generator.hpp>
#include <binary/GeneratorExtensions.hpp>
#include <binary/converters/LittleEndianConverter.hpp>
#include <binary/converters/LittleEndianStringConverter.hpp>
#include <binary/converters/VariantConverter.hpp>

namespace tests::binary::converters::VariantConverterTests {
BOOST_AUTO_TEST_SUITE(VariantConverterTests)

using VariantConverterTestTypeData = boost::mpl::list<
    std::variant<int32_t, int32_t>,
    std::variant<int32_t, int64_t, int16_t>,
    std::variant<int16_t, std::string>,
    std::variant<std::string, int32_t, int64_t>>;

BOOST_AUTO_TEST_CASE_TEMPLATE(VariantConverterLengthTest, T, VariantConverterTestTypeData) {
    ::binary::Generator generator;
    ::binary::AddConverter<::binary::converters::LittleEndianConverter<int16_t>>(generator);
    ::binary::AddConverter<::binary::converters::LittleEndianConverter<int32_t>>(generator);
    ::binary::AddConverter<::binary::converters::LittleEndianConverter<int64_t>>(generator);
    ::binary::AddConverter<::binary::converters::LittleEndianStringConverter<std::string>>(generator);
    ::binary::AddConverter<::binary::converters::VariantConverter<T>>(generator);
    auto converter = ::binary::GetConverter<T>(generator);
    BOOST_REQUIRE_EQUAL(typeid(::binary::converters::VariantConverter<T>).name(), typeid(*converter).name());
    BOOST_REQUIRE_EQUAL(0, converter->Length());
}

BOOST_AUTO_TEST_CASE_TEMPLATE(VariantConverterEncodeDecodeBothMethodsWithDefaultValueTest, T, VariantConverterTestTypeData) {
    ::binary::Generator generator;
    ::binary::AddConverter<::binary::converters::LittleEndianConverter<int16_t>>(generator);
    ::binary::AddConverter<::binary::converters::LittleEndianConverter<int32_t>>(generator);
    ::binary::AddConverter<::binary::converters::LittleEndianConverter<int64_t>>(generator);
    ::binary::AddConverter<::binary::converters::LittleEndianStringConverter<std::string>>(generator);
    ::binary::AddConverter<::binary::converters::VariantConverter<T>>(generator);
    T source(std::in_place_index<0>, decltype(std::get<0>(T())){});
    auto converter = ::binary::GetConverter<T>(generator);
    auto dataBuffer = ::binary::Allocator::Invoke([&source, &converter](auto& allocator) { converter->Encode(allocator, source); });
    auto autoBuffer = ::binary::Allocator::Invoke([&source, &converter](auto& allocator) { converter->EncodeAuto(allocator, source); });

    std::span<const std::byte> dataSpan(dataBuffer);
    std::span<const std::byte> autoSpan(autoBuffer);
    auto dataResult = converter->Decode(dataSpan);
    auto autoResult = converter->DecodeAuto(autoSpan);
    BOOST_REQUIRE_EQUAL(0, dataResult.index());
    BOOST_REQUIRE_EQUAL(0, autoResult.index());
    BOOST_REQUIRE_EQUAL(decltype(std::get<0>(T())){}, std::get<0>(dataResult));
    BOOST_REQUIRE_EQUAL(decltype(std::get<0>(T())){}, std::get<0>(autoResult));
    BOOST_REQUIRE_EQUAL(autoSpan.size(), 0);
}

BOOST_AUTO_TEST_SUITE_END()
}
