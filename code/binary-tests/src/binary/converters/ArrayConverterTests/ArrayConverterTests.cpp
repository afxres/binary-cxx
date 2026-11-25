#include <boost/test/unit_test.hpp>

#include <binary/Generator.hpp>
#include <binary/GeneratorExtensions.hpp>
#include <binary/converters/ArrayConverter.hpp>
#include <binary/converters/ContainerConverter.hpp>
#include <binary/converters/LittleEndianConverter.hpp>
#include <binary/converters/LittleEndianStringConverter.hpp>

#include <array>
#include <cstdint>
#include <stdexcept>
#include <string>
#include <vector>

namespace tests::binary::converters::ArrayConverterTests {
BOOST_AUTO_TEST_SUITE(ArrayConverterTests)

namespace {
// Aliases: `std::array<E, N>` carries a comma, which the Boost.Test macros split.
using Fixed = std::array<std::int32_t, 3>;
using Texts = std::array<std::string, 2>;
using Empty = std::array<std::int32_t, 0>;

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

// Claims a 512 MiB element, which no encoder ever sees: the array length is
// computed in the constructor, and that is what the overflow guard rejects.
class HugeLengthConverter : public ::binary::Converter<std::uint64_t> {
public:
    HugeLengthConverter()
        : ::binary::Converter<std::uint64_t>(0x20000000) {}

    void Encode(::binary::Allocator&, const std::uint64_t&) override {}

    std::uint64_t Decode(std::span<const std::byte>) override { return 0; }
};
}

BOOST_AUTO_TEST_CASE(ArrayConverterLengthTest) {
    ::binary::Generator generator;
    ::binary::AddConverter<::binary::converters::LittleEndianConverter<std::int32_t>>(generator);
    ::binary::AddConverter<::binary::converters::LittleEndianStringConverter<std::string>>(generator);
    ::binary::AddConverter<::binary::converters::ArrayConverter<Fixed>>(generator);
    ::binary::AddConverter<::binary::converters::ArrayConverter<Texts>>(generator);
    ::binary::AddConverter<::binary::converters::ArrayConverter<Empty>>(generator);

    auto numbers = ::binary::GetConverter<Fixed>(generator);
    auto texts = ::binary::GetConverter<Texts>(generator);
    auto empty = ::binary::GetConverter<Empty>(generator);
    BOOST_REQUIRE_EQUAL(12, numbers->Length());
    BOOST_REQUIRE_EQUAL(0, texts->Length());
    BOOST_REQUIRE_EQUAL(0, empty->Length());
    const auto& numbersConverter = *numbers;
    BOOST_REQUIRE_EQUAL(typeid(::binary::converters::ArrayConverter<Fixed>).name(), typeid(numbersConverter).name());
}

BOOST_AUTO_TEST_CASE(ArrayConverterWireTest) {
    // The last element keeps its own prefix: an array has no trailing member to
    // delimit it.
    ::binary::Generator generator;
    ::binary::AddConverter<::binary::converters::LittleEndianConverter<std::int32_t>>(generator);
    ::binary::AddConverter<::binary::converters::LittleEndianStringConverter<std::string>>(generator);
    ::binary::AddConverter<::binary::converters::ArrayConverter<Fixed>>(generator);
    ::binary::AddConverter<::binary::converters::ArrayConverter<Texts>>(generator);

    auto numbers = ::binary::GetConverter<Fixed>(generator);
    Fixed fixed{1, 2, 3};
    BOOST_REQUIRE_EQUAL("010000000200000003000000", EncodeHex(numbers, fixed));
    BOOST_REQUIRE_EQUAL("010000000200000003000000", EncodeAutoHex(numbers, fixed));

    auto texts = ::binary::GetConverter<Texts>(generator);
    Texts variable{"a", "b"};
    BOOST_REQUIRE_EQUAL("01610162", EncodeHex(texts, variable));
    BOOST_REQUIRE_EQUAL("0401610162", EncodeAutoHex(texts, variable));
}

BOOST_AUTO_TEST_CASE(ArrayConverterDecodeTest) {
    ::binary::Generator generator;
    ::binary::AddConverter<::binary::converters::LittleEndianConverter<std::int32_t>>(generator);
    ::binary::AddConverter<::binary::converters::ArrayConverter<Fixed>>(generator);

    auto converter = ::binary::GetConverter<Fixed>(generator);

    // `Decode` leaves the caller's span untouched, `DecodeAuto` consumes it.
    std::array<std::byte, 14> bytes{};
    for (size_t i = 0; i < 3; i++) {
        bytes[i * 4] = static_cast<std::byte>(i + 1);
    }
    std::span<const std::byte> decodeSpan(bytes);
    auto decoded = converter->Decode(decodeSpan);
    BOOST_REQUIRE_EQUAL(14, decodeSpan.size());
    BOOST_REQUIRE_EQUAL(1, decoded[0]);
    BOOST_REQUIRE_EQUAL(2, decoded[1]);
    BOOST_REQUIRE_EQUAL(3, decoded[2]);

    std::span<const std::byte> autoSpan(bytes);
    auto autoDecoded = converter->DecodeAuto(autoSpan);
    BOOST_REQUIRE_EQUAL(2, autoSpan.size());
    BOOST_REQUIRE_EQUAL(3, autoDecoded[2]);
}

BOOST_AUTO_TEST_CASE(ArrayConverterTruncatedTest) {
    ::binary::Generator generator;
    ::binary::AddConverter<::binary::converters::LittleEndianConverter<std::int32_t>>(generator);
    ::binary::AddConverter<::binary::converters::ArrayConverter<Fixed>>(generator);
    auto converter = ::binary::GetConverter<Fixed>(generator);

    std::array<std::byte, 8> shortBytes{};
    std::span<const std::byte> span(shortBytes);
    BOOST_REQUIRE_EXCEPTION(
        converter->DecodeAuto(span),
        std::length_error,
        [](const std::length_error& e) {
            BOOST_REQUIRE_EQUAL(e.what(), "not enough bytes or byte sequence invalid");
            return true;
        }
    );
}

BOOST_AUTO_TEST_CASE(ArrayConverterEmptyTest) {
    // Length zero means variable, so the empty array is written with a prefix.
    ::binary::Generator generator;
    ::binary::AddConverter<::binary::converters::LittleEndianConverter<std::int32_t>>(generator);
    ::binary::AddConverter<::binary::converters::ArrayConverter<Empty>>(generator);
    auto converter = ::binary::GetConverter<Empty>(generator);

    Empty empty{};
    BOOST_REQUIRE_EQUAL("", EncodeHex(converter, empty));
    BOOST_REQUIRE_EQUAL("00", EncodeAutoHex(converter, empty));

    std::array<std::byte, 1> bytes{std::byte{0x00}};
    std::span<const std::byte> span(bytes);
    auto result = converter->DecodeAuto(span);
    BOOST_REQUIRE_EQUAL(0, result.size());
    BOOST_REQUIRE_EQUAL(0, span.size());
}

BOOST_AUTO_TEST_CASE(ArrayConverterLengthOverflowTest) {
    // Three elements fit in the 32 bit prefix, four do not: the guard is exact,
    // not a coarse upper bound.
    using Small = std::array<std::uint64_t, 3>;
    using Huge = std::array<std::uint64_t, 4>;
    auto fits = std::make_shared<::binary::converters::ArrayConverter<Small>>(std::make_shared<HugeLengthConverter>());
    BOOST_REQUIRE_EQUAL(0x60000000, fits->Length());
    BOOST_REQUIRE_THROW((std::make_shared<::binary::converters::ArrayConverter<Huge>>(std::make_shared<HugeLengthConverter>())), std::overflow_error);
}

BOOST_AUTO_TEST_CASE(ArrayConverterInContainerTest) {
    using Source = std::vector<Fixed>;
    ::binary::Generator generator;
    ::binary::AddConverter<::binary::converters::LittleEndianConverter<std::int32_t>>(generator);
    ::binary::AddConverter<::binary::converters::ArrayConverter<Fixed>>(generator);
    ::binary::AddConverter<::binary::converters::ContainerConverter<Source>>(generator);

    auto converter = ::binary::GetConverter<Source>(generator);
    Source source{{1, 2, 3}, {4, 5, 6}};
    BOOST_REQUIRE_EQUAL("18010000000200000003000000040000000500000006000000", EncodeAutoHex(converter, source));

    auto buffer = ::binary::Allocator::Invoke([&converter, &source](auto& allocator) { converter->EncodeAuto(allocator, source); });
    std::span<const std::byte> span(buffer);
    auto result = converter->DecodeAuto(span);
    BOOST_REQUIRE_EQUAL(0, span.size());
    BOOST_REQUIRE_EQUAL(2, result.size());
    BOOST_REQUIRE_EQUAL(6, result.at(1).at(2));
}

BOOST_AUTO_TEST_SUITE_END()
}
