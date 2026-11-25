#include <boost/test/unit_test.hpp>

#include <binary/Allocator.hpp>
#include <binary/converters/LittleEndianConverter.hpp>
#include <binary/converters/LittleEndianStringConverter.hpp>

#include <binary/experimental/Converter.hpp>
#include <binary/experimental/converters/ArrayConverter.hpp>
#include <binary/experimental/helpers/ConverterDecodeAutoMethodHelper.hpp>
#include <binary/experimental/helpers/ConverterEncodeAutoMethodHelper.hpp>

#include <array>
#include <cstdint>
#include <stdexcept>
#include <string>
#include <vector>

namespace tests::binary::experimental::converters::ArrayConverterTests {
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
std::string EncodeHex(const T& item) {
    auto buffer = ::binary::Allocator::Invoke([&item](auto& allocator) { ::binary::experimental::Converter<T>::Encode(allocator, item); });
    return ToHex(buffer);
}

template <typename T>
std::string EncodeAutoHex(const T& item) {
    using C = ::binary::experimental::Converter<T>;
    auto buffer = ::binary::Allocator::Invoke([&item](auto& allocator) { ::binary::experimental::helpers::ConverterEncodeAutoMethodHelper<C>::Invoke(allocator, item); });
    return ToHex(buffer);
}
}

BOOST_AUTO_TEST_CASE(ArrayConverterLengthTest) {
    // Also the regression guard for the `TupleSize` ambiguity: `std::array` is
    // aggregate and tuple like at once.
    BOOST_REQUIRE_EQUAL(12, ::binary::experimental::Converter<Fixed>::Length());
    BOOST_REQUIRE_EQUAL(0, ::binary::experimental::Converter<Texts>::Length());
    BOOST_REQUIRE_EQUAL(0, ::binary::experimental::Converter<Empty>::Length());
}

BOOST_AUTO_TEST_CASE(ArrayConverterWireTest) {
    // Same bytes as the virtual API and the C# inline array converter.
    BOOST_REQUIRE_EQUAL("010000000200000003000000", EncodeHex(Fixed{1, 2, 3}));
    BOOST_REQUIRE_EQUAL("010000000200000003000000", EncodeAutoHex(Fixed{1, 2, 3}));
    BOOST_REQUIRE_EQUAL("01610162", EncodeHex(Texts{"a", "b"}));
    BOOST_REQUIRE_EQUAL("0401610162", EncodeAutoHex(Texts{"a", "b"}));
}

BOOST_AUTO_TEST_CASE(ArrayConverterRoundTripTest) {
    // A variable length last element stays readable -- the case a tuple
    // converter cannot serve.
    auto textBytes = ::binary::experimental::Encode(Texts{"a", "b"});
    auto texts = ::binary::experimental::Decode<Texts>(textBytes);
    BOOST_REQUIRE_EQUAL("a", texts[0]);
    BOOST_REQUIRE_EQUAL("b", texts[1]);

    using Nested = std::array<std::array<std::int32_t, 2>, 2>;
    auto nestedBytes = ::binary::experimental::Encode(Nested{{{1, 2}, {3, 4}}});
    BOOST_REQUIRE_EQUAL("01000000020000000300000004000000", ToHex(nestedBytes));
    auto nested = ::binary::experimental::Decode<Nested>(nestedBytes);
    BOOST_REQUIRE_EQUAL(4, nested[1][1]);
}

BOOST_AUTO_TEST_CASE(ArrayConverterEmptyTest) {
    BOOST_REQUIRE_EQUAL("", EncodeHex(Empty{}));
    BOOST_REQUIRE_EQUAL("00", EncodeAutoHex(Empty{}));
    auto bytes = ::binary::experimental::Encode(Empty{});
    BOOST_REQUIRE_EQUAL(0, bytes.size());
}

BOOST_AUTO_TEST_CASE(ArrayConverterInContainerTest) {
    using Source = std::vector<Fixed>;
    using SourceConverter = ::binary::experimental::Converter<Source>;
    Source source{{1, 2, 3}, {4, 5, 6}};
    BOOST_REQUIRE_EQUAL("18010000000200000003000000040000000500000006000000", EncodeAutoHex(source));

    auto bytes = ::binary::Allocator::Invoke([&source](auto& allocator) { ::binary::experimental::helpers::ConverterEncodeAutoMethodHelper<SourceConverter>::Invoke(allocator, source); });
    std::span<const std::byte> span(bytes);
    auto result = ::binary::experimental::helpers::ConverterDecodeAutoMethodHelper<SourceConverter>::Invoke(span);
    BOOST_REQUIRE_EQUAL(0, span.size());
    BOOST_REQUIRE_EQUAL(2, result.size());
    BOOST_REQUIRE_EQUAL(6, result.at(1).at(2));
}

BOOST_AUTO_TEST_CASE(ArrayConverterTruncatedTest) {
    std::array<std::byte, 8> shortBytes{};
    std::span<const std::byte> span(shortBytes);
    BOOST_REQUIRE_EXCEPTION(
        ::binary::experimental::helpers::ConverterDecodeAutoMethodHelper<::binary::experimental::Converter<Fixed>>::Invoke(span),
        std::length_error,
        [](const std::length_error& e) {
            BOOST_REQUIRE_EQUAL(e.what(), "not enough bytes or byte sequence invalid");
            return true;
        }
    );
}

BOOST_AUTO_TEST_SUITE_END()
}
