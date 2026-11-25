#include <boost/test/unit_test.hpp>

#include <binary/Generator.hpp>
#include <binary/GeneratorExtensions.hpp>
#include <binary/converters/ComplexConverter.hpp>
#include <binary/converters/ContainerConverter.hpp>
#include <binary/converters/LittleEndianConverter.hpp>

#include <array>
#include <complex>
#include <cstdint>
#include <stdexcept>
#include <string>
#include <vector>

namespace tests::binary::converters::ComplexConverterTests {
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
std::string EncodeHex(const std::shared_ptr<::binary::Converter<T>>& converter, const T& item) {
    auto buffer = ::binary::Allocator::Invoke([&converter, &item](auto& allocator) { converter->Encode(allocator, item); });
    return ToHex(buffer);
}

template <typename T>
std::string EncodeAutoHex(const std::shared_ptr<::binary::Converter<T>>& converter, const T& item) {
    auto buffer = ::binary::Allocator::Invoke([&converter, &item](auto& allocator) { converter->EncodeAuto(allocator, item); });
    return ToHex(buffer);
}
}

BOOST_AUTO_TEST_CASE(ComplexConverterLengthTest) {
    ::binary::Generator generator;
    ::binary::AddConverter<::binary::converters::LittleEndianConverter<double>>(generator);
    ::binary::AddConverter<::binary::converters::LittleEndianConverter<float>>(generator);
    ::binary::AddConverter<::binary::converters::ComplexConverter<std::complex<double>>>(generator);
    ::binary::AddConverter<::binary::converters::ComplexConverter<std::complex<float>>>(generator);

    auto wide = ::binary::GetConverter<std::complex<double>>(generator);
    auto narrow = ::binary::GetConverter<std::complex<float>>(generator);
    BOOST_REQUIRE_EQUAL(16, wide->Length());
    BOOST_REQUIRE_EQUAL(8, narrow->Length());
}

BOOST_AUTO_TEST_CASE(ComplexConverterWireTest) {
    // `complex_1_5` in wire.tsv: the bytes the C# side writes for `Complex`.
    ::binary::Generator generator;
    ::binary::AddConverter<::binary::converters::LittleEndianConverter<double>>(generator);
    ::binary::AddConverter<::binary::converters::LittleEndianConverter<float>>(generator);
    ::binary::AddConverter<::binary::converters::ComplexConverter<std::complex<double>>>(generator);
    ::binary::AddConverter<::binary::converters::ComplexConverter<std::complex<float>>>(generator);

    std::complex<double> wide{1.5, -2.25};
    auto wideConverter = ::binary::GetConverter<std::complex<double>>(generator);
    BOOST_REQUIRE_EQUAL("000000000000f83f00000000000002c0", EncodeHex(wideConverter, wide));
    BOOST_REQUIRE_EQUAL("000000000000f83f00000000000002c0", EncodeAutoHex(wideConverter, wide));

    std::complex<float> narrow{1.5F, -2.25F};
    auto narrowConverter = ::binary::GetConverter<std::complex<float>>(generator);
    BOOST_REQUIRE_EQUAL("0000c03f000010c0", EncodeHex(narrowConverter, narrow));
}

BOOST_AUTO_TEST_CASE(ComplexConverterDecodeTest) {
    ::binary::Generator generator;
    ::binary::AddConverter<::binary::converters::LittleEndianConverter<double>>(generator);
    ::binary::AddConverter<::binary::converters::ComplexConverter<std::complex<double>>>(generator);
    auto converter = ::binary::GetConverter<std::complex<double>>(generator);

    std::complex<double> source{1.5, -2.25};
    auto buffer = ::binary::Allocator::Invoke([&converter, &source](auto& allocator) { converter->Encode(allocator, source); });
    BOOST_REQUIRE_EQUAL(source, converter->Decode(buffer));
}

BOOST_AUTO_TEST_CASE(ComplexConverterTruncatedTest) {
    ::binary::Generator generator;
    ::binary::AddConverter<::binary::converters::LittleEndianConverter<double>>(generator);
    ::binary::AddConverter<::binary::converters::ComplexConverter<std::complex<double>>>(generator);
    auto converter = ::binary::GetConverter<std::complex<double>>(generator);

    std::array<std::byte, 8> shortBytes{};
    BOOST_REQUIRE_EXCEPTION(
        converter->Decode(shortBytes),
        std::length_error,
        [](const std::length_error& e) {
            BOOST_REQUIRE_EQUAL(e.what(), "not enough bytes or byte sequence invalid");
            return true;
        }
    );
}

BOOST_AUTO_TEST_CASE(ComplexConverterInContainerTest) {
    ::binary::Generator generator;
    ::binary::AddConverter<::binary::converters::LittleEndianConverter<double>>(generator);
    ::binary::AddConverter<::binary::converters::ComplexConverter<std::complex<double>>>(generator);
    ::binary::AddConverter<::binary::converters::ContainerConverter<std::vector<std::complex<double>>>>(generator);

    auto converter = ::binary::GetConverter<std::vector<std::complex<double>>>(generator);
    std::vector<std::complex<double>> source{{1.5, -2.25}};
    BOOST_REQUIRE_EQUAL("10000000000000f83f00000000000002c0", EncodeAutoHex(converter, source));
}

BOOST_AUTO_TEST_SUITE_END()
}
