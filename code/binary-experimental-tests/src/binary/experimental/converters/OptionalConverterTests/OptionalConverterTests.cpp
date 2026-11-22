#include <boost/test/unit_test.hpp>

#include <binary/Allocator.hpp>
#include <binary/converters/LittleEndianConverter.hpp>

#include <binary/experimental/Converter.hpp>
#include <binary/experimental/converters/OptionalConverter.hpp>
#include <binary/experimental/helpers/ConverterDecodeAutoMethodHelper.hpp>
#include <binary/experimental/helpers/ConverterEncodeAutoMethodHelper.hpp>

#include <array>
#include <cstdint>
#include <optional>
#include <stdexcept>
#include <string>
#include <variant>
#include <vector>

namespace tests::binary::experimental::converters::OptionalConverterTests {
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

// The template API has no `EncodeAuto` / `DecodeAuto` on the converter type
// itself when the converter only declares `Encode` (the helper adds the
// boundary). These two wrappers call the same helper the library calls, so a
// test of the auto form is testing the real path, not a copy of it.
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

template <typename T>
T DecodeAuto(std::span<const std::byte>& span) {
    using C = ::binary::experimental::Converter<T>;
    return ::binary::experimental::helpers::ConverterDecodeAutoMethodHelper<C>::Invoke(span);
}
}

BOOST_AUTO_TEST_CASE(OptionalConverterLengthTest) {
    BOOST_REQUIRE_EQUAL(0, ::binary::experimental::Converter<std::optional<std::int32_t>>::Length());
    BOOST_REQUIRE_EQUAL(0, ::binary::experimental::Converter<std::optional<std::string>>::Length());
}

BOOST_AUTO_TEST_CASE(OptionalConverterWireTest) {
    using N = std::optional<std::int32_t>;
    BOOST_REQUIRE_EQUAL("00", EncodeHex<N>(std::nullopt));
    BOOST_REQUIRE_EQUAL("00", EncodeAutoHex<N>(std::nullopt));
    BOOST_REQUIRE_EQUAL("012a000000", EncodeHex<N>(42));
    BOOST_REQUIRE_EQUAL("012a000000", EncodeAutoHex<N>(42));

    using S = std::optional<std::string>;
    BOOST_REQUIRE_EQUAL("00", EncodeHex<S>(std::nullopt));
    BOOST_REQUIRE_EQUAL("01616263", EncodeHex<S>(std::string("abc")));
    BOOST_REQUIRE_EQUAL("0103616263", EncodeAutoHex<S>(std::string("abc")));
}

BOOST_AUTO_TEST_CASE(OptionalConverterDecodeTest) {
    using N = std::optional<std::int32_t>;
    std::array<std::byte, 5> buffer{std::byte{0x01}, std::byte{0x2a}, std::byte{0x00}, std::byte{0x00}, std::byte{0x00}};
    std::span<const std::byte> span(buffer);
    auto result = DecodeAuto<N>(span);
    BOOST_REQUIRE(result.has_value());
    BOOST_REQUIRE_EQUAL(42, *result);
    BOOST_REQUIRE_EQUAL(0, span.size());

    std::array<std::byte, 1> empty{std::byte{0x00}};
    auto emptyResult = ::binary::experimental::Converter<N>::Decode(empty);
    BOOST_REQUIRE(!emptyResult.has_value());
}

BOOST_AUTO_TEST_CASE(OptionalConverterInvalidTagTest) {
    using N = std::optional<std::int32_t>;
    std::array<std::byte, 1> buffer{std::byte{0x02}};
    BOOST_REQUIRE_EXCEPTION(
        ::binary::experimental::Converter<N>::Decode(buffer),
        std::invalid_argument,
        [](const std::invalid_argument& e) {
            BOOST_REQUIRE_EQUAL(e.what(), "invalid optional tag: 2");
            return true;
        }
    );
}

BOOST_AUTO_TEST_CASE(OptionalConverterInContainerTest) {
    using N = std::optional<std::int32_t>;
    using S = std::optional<std::string>;
    std::vector<N> numbers{std::nullopt, 42, std::nullopt};
    BOOST_REQUIRE_EQUAL("0700012a00000000", EncodeAutoHex(numbers));

    std::vector<S> texts{std::nullopt, std::string("abc")};
    BOOST_REQUIRE_EQUAL("06000103616263", EncodeAutoHex(texts));
}

BOOST_AUTO_TEST_CASE(OptionalConverterMatchesVariantWithMonostateTest) {
    // Same wire as `std::variant<std::monostate, E>`; keeps the two from drifting.
    using V = std::variant<std::monostate, std::int32_t>;
    using N = std::optional<std::int32_t>;
    BOOST_REQUIRE_EQUAL(EncodeHex<V>(V(std::in_place_index<0>)), EncodeHex<N>(std::nullopt));
    BOOST_REQUIRE_EQUAL(EncodeAutoHex<V>(V(std::in_place_index<0>)), EncodeAutoHex<N>(std::nullopt));
    BOOST_REQUIRE_EQUAL(EncodeHex<V>(V(42)), EncodeHex<N>(42));
    BOOST_REQUIRE_EQUAL(EncodeAutoHex<V>(V(42)), EncodeAutoHex<N>(42));
}

BOOST_AUTO_TEST_SUITE_END()
}
