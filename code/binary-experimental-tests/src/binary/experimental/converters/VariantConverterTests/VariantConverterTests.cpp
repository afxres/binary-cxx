#include <boost/mpl/list.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/unit_test.hpp>

#include <binary/Generator.hpp>
#include <binary/GeneratorExtensions.hpp>
#include <binary/converters/LittleEndianConverter.hpp>
#include <binary/converters/LittleEndianStringConverter.hpp>
#include <binary/converters/VariantConverter.hpp>

#include <binary/experimental/Converter.hpp>

#include <cstdint>
#include <format>
#include <stdexcept>
#include <variant>

namespace tests::binary::experimental::converters::VariantConverterTests {
class FakeCopyType {
public:
    FakeCopyType() {}
    FakeCopyType(const FakeCopyType&) { throw std::logic_error("fake copy"); }
    FakeCopyType& operator=(const FakeCopyType&) = default;
};

struct FakeCopyTypeConverter {
    static constexpr size_t Length() {
        return 0;
    }

    static void Encode(::binary::Allocator&, const FakeCopyType&) {}

    static FakeCopyType Decode(std::span<const std::byte>) {
        throw std::logic_error("fake copy");
    }
};
}

namespace binary::experimental::helpers {
template <>
struct GetConverterHelper<::tests::binary::experimental::converters::VariantConverterTests::FakeCopyType> {
    using Type = ::tests::binary::experimental::converters::VariantConverterTests::FakeCopyTypeConverter;
};
}

namespace tests::binary::experimental::converters::VariantConverterTests {
BOOST_AUTO_TEST_SUITE(VariantConverterTests)

using VariantConverterTestTypeData = boost::mpl::list<
    std::variant<int32_t, int32_t>,
    std::variant<int32_t, int64_t, int16_t>,
    std::variant<int16_t, std::string>,
    std::variant<std::string, int32_t, int64_t>,
    std::variant<const int64_t, const std::string>,
    std::variant<const int16_t, int32_t, const std::string>>;

BOOST_AUTO_TEST_CASE_TEMPLATE(VariantConverterLengthTest, T, VariantConverterTestTypeData) {
    using ConverterType = ::binary::experimental::Converter<T>;
    std::string name = typeid(ConverterType).name();
    BOOST_REQUIRE(name.find("experimental") != 0);
    BOOST_REQUIRE(name.find("VariantConverter") != 0);
    BOOST_REQUIRE_EQUAL(0, ConverterType::Length());
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
    auto dataBufferOrigin = ::binary::Allocator::Invoke([&source, &converter](auto& allocator) { converter->Encode(allocator, source); });
    auto autoBufferOrigin = ::binary::Allocator::Invoke([&source, &converter](auto& allocator) { converter->EncodeAuto(allocator, source); });

    using ConverterType = ::binary::experimental::Converter<T>;
    auto dataBuffer = ::binary::Allocator::Invoke([&source](auto& allocator) { ConverterType::Encode(allocator, source); });
    auto autoBuffer = ::binary::Allocator::Invoke([&source](auto& allocator) { ConverterType::EncodeAuto(allocator, source); });
    BOOST_REQUIRE_EQUAL(std::string_view(reinterpret_cast<const char*>(dataBufferOrigin.data()), dataBufferOrigin.size()), std::string_view(reinterpret_cast<const char*>(dataBuffer.data()), dataBuffer.size()));
    BOOST_REQUIRE_EQUAL(std::string_view(reinterpret_cast<const char*>(autoBufferOrigin.data()), autoBufferOrigin.size()), std::string_view(reinterpret_cast<const char*>(autoBuffer.data()), autoBuffer.size()));

    std::span<const std::byte> dataSpan(dataBuffer);
    std::span<const std::byte> autoSpan(autoBuffer);
    auto dataResult = ConverterType::Decode(dataSpan);
    auto autoResult = ConverterType::DecodeAuto(autoSpan);
    BOOST_REQUIRE_EQUAL(0, dataResult.index());
    BOOST_REQUIRE_EQUAL(0, autoResult.index());
    BOOST_REQUIRE_EQUAL(decltype(std::get<0>(T())){}, std::get<0>(dataResult));
    BOOST_REQUIRE_EQUAL(decltype(std::get<0>(T())){}, std::get<0>(autoResult));
    BOOST_REQUIRE_EQUAL(autoSpan.size(), 0);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(VariantConverterDecodeBothMethodsWithInvalidVariantIndexTest, T, VariantConverterTestTypeData) {
    using ConverterType = ::binary::experimental::Converter<T>;
    auto dataBuffer = ::binary::Allocator::Invoke([](auto& allocator) { ::binary::Encode(allocator, std::variant_size_v<T>); });
    auto autoBuffer = std::vector<std::byte>{dataBuffer};

    std::span<const std::byte> dataSpan(dataBuffer);
    std::span<const std::byte> autoSpan(autoBuffer);
    auto message = std::format("invalid variant index: {}", std::variant_size_v<T>);
    BOOST_REQUIRE_EXCEPTION(
        ConverterType::Decode(dataSpan),
        std::invalid_argument,
        [message](const std::invalid_argument& e) {
            BOOST_REQUIRE_EQUAL(e.what(), message);
            return true;
        }
    );
    BOOST_REQUIRE_EXCEPTION(
        ConverterType::DecodeAuto(autoSpan),
        std::invalid_argument,
        [message](const std::invalid_argument& e) {
            BOOST_REQUIRE_EQUAL(e.what(), message);
            return true;
        }
    );
    BOOST_REQUIRE_EQUAL(autoSpan.size(), 0);
}

BOOST_AUTO_TEST_CASE(VariantConverterEncodeInvalidVariantTest) {
    using Type = std::variant<std::int32_t, FakeCopyType>;
    using ConverterType = ::binary::experimental::Converter<Type>;
    Type source;
    BOOST_REQUIRE_EQUAL(0, source.index());
    BOOST_REQUIRE_EXCEPTION(
        source = FakeCopyType(),
        std::logic_error,
        [](const std::logic_error& e) {
            BOOST_REQUIRE_EQUAL(e.what(), "fake copy");
            return true;
        }
    );
    BOOST_REQUIRE(source.valueless_by_exception());
    BOOST_REQUIRE_EQUAL(std::variant_npos, source.index());
    ::binary::Allocator allocator;
    auto message = std::format("invalid variant index: {}", SIZE_MAX);
    BOOST_REQUIRE_EXCEPTION(
        ConverterType::Encode(allocator, source),
        std::invalid_argument,
        [message](const std::invalid_argument& e) {
            BOOST_REQUIRE_EQUAL(e.what(), message);
            return true;
        }
    );
}

std::vector<std::string> StringData = {
    "",
    "Alice",
};

BOOST_DATA_TEST_CASE(VariantConverterWithStringDataTest, StringData, data) {
    ::binary::Generator generator;
    ::binary::AddConverter<::binary::converters::LittleEndianStringConverter<std::string>>(generator);
    ::binary::AddConverter<::binary::converters::VariantConverter<std::variant<const std::string>>>(generator);
    auto converter = ::binary::GetConverter<std::variant<const std::string>>(generator);
    std::variant<const std::string> source(data);
    auto dataBufferOrigin = ::binary::Allocator::Invoke([&source, &converter](auto& allocator) { converter->Encode(allocator, source); });
    auto autoBufferOrigin = ::binary::Allocator::Invoke([&source, &converter](auto& allocator) { converter->EncodeAuto(allocator, source); });
    BOOST_REQUIRE_LT(dataBufferOrigin.size(), autoBufferOrigin.size());

    using ConverterType = ::binary::experimental::Converter<decltype(source)>;
    auto dataBuffer = ::binary::Allocator::Invoke([&source](auto& allocator) { ConverterType::Encode(allocator, source); });
    auto autoBuffer = ::binary::Allocator::Invoke([&source](auto& allocator) { ConverterType::EncodeAuto(allocator, source); });
    BOOST_REQUIRE_EQUAL(std::string_view(reinterpret_cast<const char*>(dataBufferOrigin.data()), dataBufferOrigin.size()), std::string_view(reinterpret_cast<const char*>(dataBuffer.data()), dataBuffer.size()));
    BOOST_REQUIRE_EQUAL(std::string_view(reinterpret_cast<const char*>(autoBufferOrigin.data()), autoBufferOrigin.size()), std::string_view(reinterpret_cast<const char*>(autoBuffer.data()), autoBuffer.size()));

    std::span<const std::byte> dataSpan(dataBuffer);
    std::span<const std::byte> autoSpan(autoBuffer);
    auto dataResult = ConverterType::Decode(dataSpan);
    auto autoResult = ConverterType::DecodeAuto(autoSpan);
    BOOST_REQUIRE(source == dataResult);
    BOOST_REQUIRE(source == autoResult);
    BOOST_REQUIRE_EQUAL(autoSpan.size(), 0);
}

BOOST_AUTO_TEST_SUITE_END()
}
