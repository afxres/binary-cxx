#include <boost/test/data/test_case.hpp>
#include <boost/test/unit_test.hpp>

#include <binary/Converter.hpp>

namespace tests::binary::ConverterTests {
BOOST_AUTO_TEST_SUITE(ConverterTests)

using ::binary::Allocator;
using ::binary::Converter;

template <typename T>
class FakeEmptyConverter : public Converter<T> {
    using Converter<T>::Converter;

    void Encode([[maybe_unused]] Allocator& allocator, [[maybe_unused]] const T& item) override {
        throw std::exception();
    }

    T Decode([[maybe_unused]] const std::span<const std::byte>& span) override {
        throw std::exception();
    }
};

BOOST_AUTO_TEST_CASE(ConverterDefaultLengthTest) {
    FakeEmptyConverter<int32_t> converter{};
    BOOST_REQUIRE_EQUAL(converter.Length(), 0);
}

std::vector<size_t> ConverterCustomLengthData = {0, 1, 4, 128, 1024};

BOOST_DATA_TEST_CASE(ConverterCustomLengthTests, ConverterCustomLengthData) {
    FakeEmptyConverter<int32_t> converter(sample);
    BOOST_REQUIRE_EQUAL(converter.Length(), sample);
}

std::vector<size_t> ConverterInvalidLengthData = {0x8000'0000, 0x8000'0001, 0xFFFF'FFFF};

BOOST_DATA_TEST_CASE(ConverterInvalidLengthTest, ConverterInvalidLengthData) {
    BOOST_REQUIRE_EXCEPTION(
        FakeEmptyConverter<int32_t> ignore(sample),
        std::invalid_argument,
        [](const std::invalid_argument& e) {
            BOOST_REQUIRE_EQUAL(e.what(), "length > INT32_MAX");
            return true;
        });
}

std::vector<size_t> ConverterDecodeAutoNotEnoughBytesData = {1, 2, 4, 8};

BOOST_DATA_TEST_CASE(ConverterDecodeAutoNotEnoughBytesTest, ConverterDecodeAutoNotEnoughBytesData) {
    BOOST_REQUIRE_NE(0, sample);
    FakeEmptyConverter<int32_t> converter(sample);
    BOOST_REQUIRE_EQUAL(sample, converter.Length());
    std::span<const std::byte> span(static_cast<const std::byte*>(nullptr), sample - 1);

    BOOST_REQUIRE_EXCEPTION(
        converter.DecodeAuto(span),
        std::length_error,
        [](const std::length_error& e) {
            BOOST_REQUIRE_EQUAL(e.what(), "not enough bytes or byte sequence invalid");
            return true;
        });
    BOOST_REQUIRE_EQUAL(span.data(), nullptr);
    BOOST_REQUIRE_EQUAL(span.size(), sample - 1);
}

BOOST_AUTO_TEST_SUITE_END()
}
