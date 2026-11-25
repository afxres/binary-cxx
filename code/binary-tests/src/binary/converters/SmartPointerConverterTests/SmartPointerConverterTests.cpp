#include <boost/test/unit_test.hpp>

#include <binary/Generator.hpp>
#include <binary/GeneratorExtensions.hpp>
#include <binary/converters/ContainerConverter.hpp>
#include <binary/converters/LittleEndianConverter.hpp>
#include <binary/converters/LittleEndianStringConverter.hpp>
#include <binary/converters/SmartPointerConverter.hpp>

#include <cstdint>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

namespace tests::binary::converters::SmartPointerConverterTests {
BOOST_AUTO_TEST_SUITE(SmartPointerConverterTests)

namespace {
std::string ToHex(std::span<const std::byte> span) {
    static constexpr std::string_view Digits = "0123456789abcdef";
    std::string result;
    result.reserve(span.size() * 2);
    for (std::byte i : span) {
        auto value = static_cast<size_t>(i);
        result.push_back(Digits[value / 16]);
        result.push_back(Digits[value % 16]);
    }
    return result;
}

template <typename T>
std::string EncodeHex(const std::shared_ptr<::binary::Converter<T>>& converter, const T& item) {
    auto buffer = ::binary::Allocator::Invoke([&converter, &item](auto& allocator) { converter->Encode(allocator, item); });
    return ToHex(buffer);
}

template <typename T>
std::string EncodeAutoHex(const std::shared_ptr<::binary::Converter<T>>& converter, const T& item) {
    auto buffer = ::binary::Allocator::Invoke([&converter, &item](auto& allocator) { converter->EncodeAuto(allocator, item); });
    return ToHex(buffer);
}

template <typename T>
std::vector<std::byte> EncodeAutoToBuffer(const std::shared_ptr<::binary::Converter<T>>& converter, const T& item) {
    return ::binary::Allocator::Invoke([&converter, &item](auto& allocator) { converter->EncodeAuto(allocator, item); });
}

::binary::Generator MakeGenerator() {
    ::binary::Generator generator;
    ::binary::AddConverter<::binary::converters::LittleEndianConverter<std::int32_t>>(generator);
    ::binary::AddConverter<::binary::converters::LittleEndianStringConverter<std::string>>(generator);
    ::binary::AddConverter<::binary::converters::SmartPointerConverter<std::unique_ptr<std::int32_t>>>(generator);
    ::binary::AddConverter<::binary::converters::SmartPointerConverter<std::shared_ptr<std::int32_t>>>(generator);
    ::binary::AddConverter<::binary::converters::SmartPointerConverter<std::unique_ptr<std::string>>>(generator);
    ::binary::AddConverter<::binary::converters::SmartPointerConverter<std::shared_ptr<std::string>>>(generator);
    return generator;
}
}

BOOST_AUTO_TEST_CASE(SmartPointerConverterLengthTest) {
    auto generator = MakeGenerator();
    // The length belongs to the pointee, never to the pointer: a container of
    // pointers keeps the element size of the pointee.
    BOOST_REQUIRE_EQUAL(4, ::binary::GetConverter<std::unique_ptr<std::int32_t>>(generator)->Length());
    BOOST_REQUIRE_EQUAL(4, ::binary::GetConverter<std::shared_ptr<std::int32_t>>(generator)->Length());
    BOOST_REQUIRE_EQUAL(0, ::binary::GetConverter<std::unique_ptr<std::string>>(generator)->Length());
    BOOST_REQUIRE_EQUAL(0, ::binary::GetConverter<std::shared_ptr<std::string>>(generator)->Length());
}

BOOST_AUTO_TEST_CASE(SmartPointerConverterWireTest) {
    auto generator = MakeGenerator();

    auto integer = ::binary::GetConverter<std::unique_ptr<std::int32_t>>(generator);
    BOOST_REQUIRE_EQUAL("05000000", EncodeHex(integer, std::make_unique<std::int32_t>(5)));
    BOOST_REQUIRE_EQUAL("05000000", EncodeAutoHex(integer, std::make_unique<std::int32_t>(5)));

    auto shared = ::binary::GetConverter<std::shared_ptr<std::int32_t>>(generator);
    BOOST_REQUIRE_EQUAL("05000000", EncodeHex(shared, std::make_shared<std::int32_t>(5)));

    // A variable length pointee keeps its own boundary: the pointer adds nothing.
    auto text = ::binary::GetConverter<std::unique_ptr<std::string>>(generator);
    BOOST_REQUIRE_EQUAL("616263", EncodeHex(text, std::make_unique<std::string>("abc")));
    BOOST_REQUIRE_EQUAL("03616263", EncodeAutoHex(text, std::make_unique<std::string>("abc")));
}

BOOST_AUTO_TEST_CASE(SmartPointerConverterPrefixTest) {
    auto generator = MakeGenerator();
    auto converter = ::binary::GetConverter<std::unique_ptr<std::int32_t>>(generator);
    auto buffer = ::binary::Allocator::Invoke([&converter](auto& allocator) {
        converter->EncodeWithLengthPrefix(allocator, std::make_unique<std::int32_t>(5));
    });
    BOOST_REQUIRE_EQUAL("0405000000", ToHex(buffer));
}

BOOST_AUTO_TEST_CASE(SmartPointerConverterRoundTripTest) {
    auto generator = MakeGenerator();
    auto converter = ::binary::GetConverter<std::shared_ptr<std::string>>(generator);

    auto bytes = EncodeAutoToBuffer(converter, std::make_shared<std::string>("abc"));
    std::span<const std::byte> span(bytes);
    auto first = converter->DecodeAuto(span);
    BOOST_REQUIRE_EQUAL(0, span.size());
    BOOST_REQUIRE(first != nullptr);
    BOOST_REQUIRE_EQUAL("abc", *first);

    // Object identity is not part of the format: one value decodes into two
    // independent allocations.
    std::span<const std::byte> again(bytes);
    auto second = converter->DecodeAuto(again);
    BOOST_REQUIRE(first != second);
    *second = "xyz";
    BOOST_REQUIRE_EQUAL("abc", *first);
}

BOOST_AUTO_TEST_CASE(SmartPointerConverterRawDecodeTest) {
    auto generator = MakeGenerator();

    // `Decode` forwards to the pointee unchanged, so no prefix is read and the
    // caller owns the boundary of a variable length pointee.
    std::byte integer[] = {std::byte{0x05}, std::byte{0x00}, std::byte{0x00}, std::byte{0x00}};
    BOOST_REQUIRE_EQUAL(5, *::binary::GetConverter<std::unique_ptr<std::int32_t>>(generator)->Decode(integer));
    BOOST_REQUIRE_EQUAL(5, *::binary::GetConverter<std::shared_ptr<std::int32_t>>(generator)->Decode(integer));

    std::byte text[] = {std::byte{'a'}, std::byte{'b'}, std::byte{'c'}};
    BOOST_REQUIRE_EQUAL("abc", *::binary::GetConverter<std::unique_ptr<std::string>>(generator)->Decode(text));
    BOOST_REQUIRE_EQUAL("abc", *::binary::GetConverter<std::shared_ptr<std::string>>(generator)->Decode(text));
}

BOOST_AUTO_TEST_CASE(SmartPointerConverterPrefixEntryTest) {
    auto generator = MakeGenerator();

    // The prefix comes from the pointee pair, not from an anchor: a fixed length
    // pointee yields its exact width, a variable length one its own prefix.
    auto integer = ::binary::GetConverter<std::shared_ptr<std::int32_t>>(generator);
    auto integerBytes = ::binary::Allocator::Invoke([&integer](auto& allocator) {
        integer->EncodeWithLengthPrefix(allocator, std::make_shared<std::int32_t>(5));
    });
    BOOST_REQUIRE_EQUAL("0405000000", ToHex(integerBytes));

    auto text = ::binary::GetConverter<std::shared_ptr<std::string>>(generator);
    auto textBytes = ::binary::Allocator::Invoke([&text](auto& allocator) {
        text->EncodeWithLengthPrefix(allocator, std::make_shared<std::string>("abc"));
    });
    BOOST_REQUIRE_EQUAL("03616263", ToHex(textBytes));

    std::span<const std::byte> integerSpan(integerBytes);
    BOOST_REQUIRE_EQUAL(5, *integer->DecodeWithLengthPrefix(integerSpan));
    BOOST_REQUIRE_EQUAL(0, integerSpan.size());

    std::span<const std::byte> textSpan(textBytes);
    BOOST_REQUIRE_EQUAL("abc", *text->DecodeWithLengthPrefix(textSpan));
    BOOST_REQUIRE_EQUAL(0, textSpan.size());

    auto uniqueText = ::binary::GetConverter<std::unique_ptr<std::string>>(generator);
    std::span<const std::byte> uniqueSpan(textBytes);
    BOOST_REQUIRE_EQUAL("abc", *uniqueText->DecodeWithLengthPrefix(uniqueSpan));
    BOOST_REQUIRE_EQUAL(0, uniqueSpan.size());
}

BOOST_AUTO_TEST_CASE(SmartPointerConverterNullTest) {
    auto generator = MakeGenerator();

    auto unique = ::binary::GetConverter<std::unique_ptr<std::int32_t>>(generator);
    BOOST_REQUIRE_EXCEPTION(
        EncodeHex(unique, std::unique_ptr<std::int32_t>()),
        std::invalid_argument,
        [](const std::invalid_argument& e) { return std::string(e.what()).starts_with("null pointer"); }
    );

    auto shared = ::binary::GetConverter<std::shared_ptr<std::int32_t>>(generator);
    BOOST_REQUIRE_EXCEPTION(
        EncodeHex(shared, std::shared_ptr<std::int32_t>()),
        std::invalid_argument,
        [](const std::invalid_argument& e) { return std::string(e.what()).starts_with("null pointer"); }
    );
}

BOOST_AUTO_TEST_CASE(SmartPointerConverterInContainerTest) {
    ::binary::Generator generator;
    ::binary::AddConverter<::binary::converters::LittleEndianConverter<std::int32_t>>(generator);
    ::binary::AddConverter<::binary::converters::SmartPointerConverter<std::unique_ptr<std::int32_t>>>(generator);
    ::binary::AddConverter<::binary::converters::ContainerConverter<std::vector<std::unique_ptr<std::int32_t>>>>(generator);
    ::binary::AddConverter<::binary::converters::ContainerConverter<std::vector<std::int32_t>>>(generator);

    std::vector<std::unique_ptr<std::int32_t>> pointers;
    pointers.push_back(std::make_unique<std::int32_t>(1));
    pointers.push_back(std::make_unique<std::int32_t>(2));
    pointers.push_back(std::make_unique<std::int32_t>(3));

    auto pointerConverter = ::binary::GetConverter<std::vector<std::unique_ptr<std::int32_t>>>(generator);
    auto valueConverter = ::binary::GetConverter<std::vector<std::int32_t>>(generator);
    BOOST_REQUIRE_EQUAL("0c010000000200000003000000", EncodeAutoHex(pointerConverter, pointers));
    BOOST_REQUIRE_EQUAL(EncodeAutoHex(valueConverter, std::vector<std::int32_t>{1, 2, 3}), EncodeAutoHex(pointerConverter, pointers));

    auto bytes = ::binary::Allocator::Invoke([&pointerConverter, &pointers](auto& allocator) { pointerConverter->EncodeAuto(allocator, pointers); });
    std::span<const std::byte> span(bytes);
    auto result = pointerConverter->DecodeAuto(span);
    BOOST_REQUIRE_EQUAL(0, span.size());
    BOOST_REQUIRE_EQUAL(3, result.size());
    BOOST_REQUIRE_EQUAL(2, *result.at(1));
}

BOOST_AUTO_TEST_CASE(SmartPointerConverterVariableElementTest) {
    ::binary::Generator generator;
    ::binary::AddConverter<::binary::converters::LittleEndianStringConverter<std::string>>(generator);
    ::binary::AddConverter<::binary::converters::SmartPointerConverter<std::unique_ptr<std::string>>>(generator);
    ::binary::AddConverter<::binary::converters::ContainerConverter<std::vector<std::unique_ptr<std::string>>>>(generator);

    std::vector<std::unique_ptr<std::string>> source;
    source.push_back(std::make_unique<std::string>("a"));
    source.push_back(std::make_unique<std::string>("b"));

    auto converter = ::binary::GetConverter<std::vector<std::unique_ptr<std::string>>>(generator);
    BOOST_REQUIRE_EQUAL("0401610162", EncodeAutoHex(converter, source));
}

BOOST_AUTO_TEST_SUITE_END()
}
