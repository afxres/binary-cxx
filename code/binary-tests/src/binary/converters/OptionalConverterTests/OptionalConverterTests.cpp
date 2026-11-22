#include <boost/test/unit_test.hpp>

#include <binary/Generator.hpp>
#include <binary/GeneratorExtensions.hpp>
#include <binary/converters/ContainerConverter.hpp>
#include <binary/converters/LittleEndianConverter.hpp>
#include <binary/converters/LittleEndianStringConverter.hpp>
#include <binary/converters/OptionalConverter.hpp>
#include <binary/converters/VariantConverter.hpp>

#include <array>
#include <cstdint>
#include <optional>
#include <stdexcept>
#include <string>
#include <variant>
#include <vector>

namespace tests::binary::converters::OptionalConverterTests {
BOOST_AUTO_TEST_SUITE(OptionalConverterTests)

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

// The value type is a separate template parameter so that `std::nullopt` and
// `42` can be passed for an `optional<T>` converter: deducing it from both
// arguments would make the two deductions disagree.
template <typename T, typename U>
std::string EncodeHex(const std::shared_ptr<::binary::Converter<T>>& converter, const U& item) {
    auto buffer = ::binary::Allocator::Invoke([&converter, &item](auto& allocator) { converter->Encode(allocator, item); });
    return ToHex(buffer);
}

template <typename T, typename U>
std::string EncodeAutoHex(const std::shared_ptr<::binary::Converter<T>>& converter, const U& item) {
    auto buffer = ::binary::Allocator::Invoke([&converter, &item](auto& allocator) { converter->EncodeAuto(allocator, item); });
    return ToHex(buffer);
}
}

BOOST_AUTO_TEST_CASE(OptionalConverterLengthTest) {
    ::binary::Generator generator;
    ::binary::AddConverter<::binary::converters::LittleEndianConverter<std::int32_t>>(generator);
    ::binary::AddConverter<::binary::converters::LittleEndianStringConverter<std::string>>(generator);
    ::binary::AddConverter<::binary::converters::OptionalConverter<std::optional<std::int32_t>>>(generator);
    ::binary::AddConverter<::binary::converters::OptionalConverter<std::optional<std::string>>>(generator);

    auto number = ::binary::GetConverter<std::optional<std::int32_t>>(generator);
    auto text = ::binary::GetConverter<std::optional<std::string>>(generator);
    BOOST_REQUIRE_EQUAL(0, number->Length());
    BOOST_REQUIRE_EQUAL(0, text->Length());
    const auto& numberConverter = *number;
    BOOST_REQUIRE_EQUAL(typeid(::binary::converters::OptionalConverter<std::optional<std::int32_t>>).name(), typeid(numberConverter).name());
}

BOOST_AUTO_TEST_CASE(OptionalConverterWireTest) {
    // The tag is a length prefix (0 = empty, 1 = value), and the payload follows
    // the entry point: `Encode` raw, `EncodeAuto` self-delimited.
    ::binary::Generator generator;
    ::binary::AddConverter<::binary::converters::LittleEndianConverter<std::int32_t>>(generator);
    ::binary::AddConverter<::binary::converters::LittleEndianStringConverter<std::string>>(generator);
    ::binary::AddConverter<::binary::converters::OptionalConverter<std::optional<std::int32_t>>>(generator);
    ::binary::AddConverter<::binary::converters::OptionalConverter<std::optional<std::string>>>(generator);

    auto number = ::binary::GetConverter<std::optional<std::int32_t>>(generator);
    BOOST_REQUIRE_EQUAL("00", EncodeHex(number, std::nullopt));
    BOOST_REQUIRE_EQUAL("00", EncodeAutoHex(number, std::nullopt));
    BOOST_REQUIRE_EQUAL("012a000000", EncodeHex(number, 42));
    BOOST_REQUIRE_EQUAL("012a000000", EncodeAutoHex(number, 42));

    auto text = ::binary::GetConverter<std::optional<std::string>>(generator);
    BOOST_REQUIRE_EQUAL("00", EncodeHex(text, std::nullopt));
    BOOST_REQUIRE_EQUAL("00", EncodeAutoHex(text, std::nullopt));
    BOOST_REQUIRE_EQUAL("01616263", EncodeHex(text, std::string("abc")));
    BOOST_REQUIRE_EQUAL("0103616263", EncodeAutoHex(text, std::string("abc")));
}

BOOST_AUTO_TEST_CASE(OptionalConverterDecodeTest) {
    ::binary::Generator generator;
    ::binary::AddConverter<::binary::converters::LittleEndianConverter<std::int32_t>>(generator);
    ::binary::AddConverter<::binary::converters::OptionalConverter<std::optional<std::int32_t>>>(generator);

    auto converter = ::binary::GetConverter<std::optional<std::int32_t>>(generator);

    std::array<std::byte, 1> empty{std::byte{0x00}};
    auto emptyResult = converter->Decode(empty);
    BOOST_REQUIRE(!emptyResult.has_value());

    std::array<std::byte, 5> filled{std::byte{0x01}, std::byte{0x2a}, std::byte{0x00}, std::byte{0x00}, std::byte{0x00}};
    std::span<const std::byte> filledSpan(filled);
    auto filledResult = converter->DecodeAuto(filledSpan);
    BOOST_REQUIRE(filledResult.has_value());
    BOOST_REQUIRE_EQUAL(42, *filledResult);
    BOOST_REQUIRE_EQUAL(0, filledSpan.size());
}

BOOST_AUTO_TEST_CASE(OptionalConverterInvalidTagTest) {
    // Only 0 and 1 are valid, in both the 1-byte and the 4-byte tag form.
    ::binary::Generator generator;
    ::binary::AddConverter<::binary::converters::LittleEndianConverter<std::int32_t>>(generator);
    ::binary::AddConverter<::binary::converters::OptionalConverter<std::optional<std::int32_t>>>(generator);
    auto converter = ::binary::GetConverter<std::optional<std::int32_t>>(generator);

    std::array<std::byte, 1> shortTag{std::byte{0x02}};
    BOOST_REQUIRE_EXCEPTION(
        converter->Decode(shortTag),
        std::invalid_argument,
        [](const std::invalid_argument& e) {
            BOOST_REQUIRE_EQUAL(e.what(), "invalid optional tag: 2");
            return true;
        }
    );

    std::array<std::byte, 4> wideTag{std::byte{0x80}, std::byte{0x00}, std::byte{0x00}, std::byte{0x02}};
    BOOST_REQUIRE_EXCEPTION(
        converter->Decode(wideTag),
        std::invalid_argument,
        [](const std::invalid_argument& e) {
            BOOST_REQUIRE_EQUAL(e.what(), "invalid optional tag: 2");
            return true;
        }
    );
}

BOOST_AUTO_TEST_CASE(OptionalConverterInContainerTest) {
    ::binary::Generator generator;
    ::binary::AddConverter<::binary::converters::LittleEndianConverter<std::int32_t>>(generator);
    ::binary::AddConverter<::binary::converters::LittleEndianStringConverter<std::string>>(generator);
    ::binary::AddConverter<::binary::converters::OptionalConverter<std::optional<std::int32_t>>>(generator);
    ::binary::AddConverter<::binary::converters::OptionalConverter<std::optional<std::string>>>(generator);
    ::binary::AddConverter<::binary::converters::ContainerConverter<std::vector<std::optional<std::int32_t>>>>(generator);
    ::binary::AddConverter<::binary::converters::ContainerConverter<std::vector<std::optional<std::string>>>>(generator);

    auto numbers = ::binary::GetConverter<std::vector<std::optional<std::int32_t>>>(generator);
    std::vector<std::optional<std::int32_t>> numberSource{std::nullopt, 42, std::nullopt};
    BOOST_REQUIRE_EQUAL("0700012a00000000", EncodeAutoHex(numbers, numberSource));

    auto texts = ::binary::GetConverter<std::vector<std::optional<std::string>>>(generator);
    std::vector<std::optional<std::string>> textSource{std::nullopt, std::string("abc")};
    BOOST_REQUIRE_EQUAL("06000103616263", EncodeAutoHex(texts, textSource));
}

BOOST_AUTO_TEST_CASE(OptionalConverterMatchesVariantWithMonostateTest) {
    // `std::optional<E>` and `std::variant<std::monostate, E>` share one wire; this
    // is the assertion that keeps the two implementations from drifting apart.
    // The variant side is already pinned by `VariantConverterWithMonostateTest`.
    using V = std::variant<std::monostate, std::int32_t>;
    ::binary::Generator generator;
    ::binary::AddConverter<::binary::converters::LittleEndianConverter<std::int32_t>>(generator);
    ::binary::AddConverter<::binary::converters::OptionalConverter<std::optional<std::int32_t>>>(generator);
    ::binary::AddConverter<::binary::converters::VariantConverter<V>>(generator);

    auto optionalConverter = ::binary::GetConverter<std::optional<std::int32_t>>(generator);
    auto variantConverter = ::binary::GetConverter<V>(generator);

    BOOST_REQUIRE_EQUAL(EncodeHex(variantConverter, V(std::in_place_index<0>)), EncodeHex(optionalConverter, std::nullopt));
    BOOST_REQUIRE_EQUAL(EncodeAutoHex(variantConverter, V(std::in_place_index<0>)), EncodeAutoHex(optionalConverter, std::nullopt));
    BOOST_REQUIRE_EQUAL(EncodeHex(variantConverter, V(42)), EncodeHex(optionalConverter, 42));
    BOOST_REQUIRE_EQUAL(EncodeAutoHex(variantConverter, V(42)), EncodeAutoHex(optionalConverter, 42));
}

BOOST_AUTO_TEST_SUITE_END()
}
