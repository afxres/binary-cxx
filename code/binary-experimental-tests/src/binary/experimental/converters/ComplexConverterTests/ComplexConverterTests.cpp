#include <boost/test/unit_test.hpp>

#include <binary/Allocator.hpp>

#include <binary/experimental/Converter.hpp>
#include <binary/experimental/converters/ComplexConverter.hpp>
#include <binary/experimental/converters/ContainerConverter.hpp>
#include <binary/experimental/converters/LittleEndianConverter.hpp>
#include <binary/experimental/helpers/ConverterDecodeAutoMethodHelper.hpp>
#include <binary/experimental/helpers/ConverterEncodeAutoMethodHelper.hpp>

#include <array>
#include <complex>
#include <cstdint>
#include <stdexcept>
#include <string>
#include <vector>

namespace tests::binary::experimental::converters::ComplexConverterTests {
BOOST_AUTO_TEST_SUITE(ComplexConverterTests)

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

BOOST_AUTO_TEST_CASE(ComplexConverterLengthTest) {
    BOOST_REQUIRE_EQUAL(16, ::binary::experimental::Converter<std::complex<double>>::Length());
    BOOST_REQUIRE_EQUAL(8, ::binary::experimental::Converter<std::complex<float>>::Length());
}

BOOST_AUTO_TEST_CASE(ComplexConverterWireTest) {
    // `complex_1_5` in wire.tsv: the bytes the C# side writes for `Complex`.
    std::complex<double> wide{1.5, -2.25};
    BOOST_REQUIRE_EQUAL("000000000000f83f00000000000002c0", EncodeHex(wide));
    BOOST_REQUIRE_EQUAL("000000000000f83f00000000000002c0", EncodeAutoHex(wide));

    std::complex<float> narrow{1.5F, -2.25F};
    BOOST_REQUIRE_EQUAL("0000c03f000010c0", EncodeHex(narrow));
}

BOOST_AUTO_TEST_CASE(ComplexConverterRoundTripTest) {
    using T = std::complex<double>;
    T source{1.5, -2.25};
    auto bytes = ::binary::experimental::Encode(source);
    BOOST_REQUIRE_EQUAL(source, ::binary::experimental::Decode<T>(bytes));
}

BOOST_AUTO_TEST_CASE(ComplexConverterTruncatedTest) {
    std::array<std::byte, 8> shortBytes{};
    BOOST_REQUIRE_EXCEPTION(
        ::binary::experimental::Decode<std::complex<double>>(shortBytes),
        std::length_error,
        [](const std::length_error& e) {
            BOOST_REQUIRE_EQUAL(e.what(), "not enough bytes or byte sequence invalid");
            return true;
        }
    );
}

BOOST_AUTO_TEST_CASE(ComplexConverterInContainerTest) {
    using Source = std::vector<std::complex<double>>;
    Source source{{1.5, -2.25}};
    BOOST_REQUIRE_EQUAL("10000000000000f83f00000000000002c0", EncodeAutoHex(source));

    auto bytes = ::binary::Allocator::Invoke([&source](auto& allocator) { ::binary::experimental::helpers::ConverterEncodeAutoMethodHelper<::binary::experimental::Converter<Source>>::Invoke(allocator, source); });
    std::span<const std::byte> span(bytes);
    auto result = ::binary::experimental::helpers::ConverterDecodeAutoMethodHelper<::binary::experimental::Converter<Source>>::Invoke(span);
    BOOST_REQUIRE_EQUAL(0, span.size());
    BOOST_REQUIRE_EQUAL(source.front(), result.front());
}

BOOST_AUTO_TEST_SUITE_END()
}
