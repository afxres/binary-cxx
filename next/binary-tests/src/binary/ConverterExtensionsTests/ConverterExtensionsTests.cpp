#include <boost/test/data/test_case.hpp>
#include <boost/test/unit_test.hpp>

#include <binary/Allocator.hpp>
#include <binary/ConverterExtensions.hpp>

#include <array>

namespace tests::binary::ConverterExtensionsTests {
BOOST_AUTO_TEST_SUITE(ConverterExtensionsTests)

std::vector<std::tuple<size_t, std::string>> EncodeNumberTestData = {
    {0, std::string("\x00", 1)},
    {1, std::string("\x01", 1)},
    {127, std::string("\x7F", 1)},
    {128, std::string("\x80\x00\x00\x80", 4)},
    {65535, std::string("\x80\x00\xFF\xFF", 4)},
    {65536, std::string("\x80\x01\x00\x00", 4)},
    {INT32_MAX, std::string("\xFF\xFF\xFF\xFF", 4)},
};

BOOST_DATA_TEST_CASE(EncodeNumberWithAllocatorTest, EncodeNumberTestData, number, buffer) {
    ::binary::Allocator allocator;
    ::binary::Encode(allocator, number);
    auto span = allocator.AsSpan();
    BOOST_REQUIRE_EQUAL(buffer.size(), span.size());
    BOOST_REQUIRE_EQUAL(buffer, std::string(reinterpret_cast<const char*>(span.data()), span.size()));
}

BOOST_DATA_TEST_CASE(EncodeNumberWithAllocatorInvalidNumberTest, boost::unit_test::data::make<size_t>({static_cast<uint32_t>(INT32_MAX) + 1, UINT32_MAX}), number) {
    ::binary::Allocator allocator;
    BOOST_REQUIRE_EXCEPTION(
        ::binary::Encode(allocator, number),
        std::invalid_argument,
        [](const std::invalid_argument& e) {
            BOOST_REQUIRE_EQUAL(e.what(), "number > INT32_MAX");
            return true;
        });
    BOOST_REQUIRE_EQUAL(0, allocator.Length());
    BOOST_REQUIRE_EQUAL(0, allocator.Capacity());
}

BOOST_DATA_TEST_CASE(EncodeNumberWithSpanValueTest, EncodeNumberTestData, number, buffer) {
    std::array<std::byte, 16> target;
    size_t bytesWritten;
    ::binary::Encode(target, number, bytesWritten);
    BOOST_REQUIRE_EQUAL(buffer.size(), bytesWritten);
    BOOST_REQUIRE_EQUAL(buffer, std::string(reinterpret_cast<const char*>(target.data()), bytesWritten));
}

BOOST_DATA_TEST_CASE(EncodeNumberWithSpanValueInvalidNumberTest, boost::unit_test::data::make<size_t>({static_cast<uint32_t>(INT32_MAX) + 1, UINT32_MAX}), number) {
    std::array<std::byte, 16> target{};
    size_t bytesWritten = 0;
    BOOST_REQUIRE_EXCEPTION(
        ::binary::Encode(target, number, bytesWritten),
        std::invalid_argument,
        [](const std::invalid_argument& e) {
            BOOST_REQUIRE_EQUAL(e.what(), "number > INT32_MAX");
            return true;
        });
    BOOST_REQUIRE(std::all_of(target.begin(), target.end(), [](auto i) { return i == std::byte{0}; }));
    BOOST_REQUIRE_EQUAL(0, bytesWritten);
}

BOOST_DATA_TEST_CASE(EncodeNumberWithSpanValueNotEnoughBytesToWriteTest, EncodeNumberTestData, number, buffer) {
    std::array<std::byte, 16> values{};
    std::span<std::byte> target(values.data(), buffer.size() - 1);
    size_t bytesWritten = 0;
    BOOST_REQUIRE_EXCEPTION(
        ::binary::Encode(target, number, bytesWritten),
        std::length_error,
        [](const std::length_error& e) {
            BOOST_REQUIRE_EQUAL(e.what(), "not enough bytes to write");
            return true;
        });
    BOOST_REQUIRE(std::all_of(values.begin(), values.end(), [](auto i) { return i == std::byte{0}; }));
    BOOST_REQUIRE_EQUAL(0, bytesWritten);
}

std::vector<std::tuple<size_t, size_t>> EncodeWithLengthPrefixTestData = {
    {0, 1},
    {127, 128},
    {128, 132},
    {65535, 65539},
};

BOOST_DATA_TEST_CASE(EncodeWithLengthPrefixTest, EncodeWithLengthPrefixTestData, dataLength, allocatorLength) {
    std::string source(dataLength, 'x');
    ::binary::Allocator allocator;
    ::binary::EncodeWithLengthPrefix(allocator, std::span(reinterpret_cast<const std::byte*>(source.data()), source.size()));
    BOOST_REQUIRE_EQUAL(allocator.Length(), allocatorLength);
    auto span = allocator.AsSpan();
    auto result = ::binary::DecodeWithLengthPrefix(span);
    BOOST_REQUIRE_EQUAL(span.size(), 0);
    BOOST_REQUIRE_EQUAL(result.size(), dataLength);
    BOOST_REQUIRE_EQUAL(source, std::string(reinterpret_cast<const char*>(result.data()), result.size()));
}

std::vector<std::tuple<size_t, size_t>> EncodeWithLengthPrefixMaxCapacityExceededTestData = {
    {0, 0},
    {127, 127},
    {128, 131},
    {65535, 65538},
};

BOOST_DATA_TEST_CASE(EncodeWithLengthPrefixMaxCapacityExceededTest, EncodeWithLengthPrefixMaxCapacityExceededTestData, dataLength, allocatorMaxCapacity) {
    std::string source(dataLength, 'x');
    ::binary::Allocator allocator(allocatorMaxCapacity);
    BOOST_REQUIRE_EXCEPTION(
        ::binary::EncodeWithLengthPrefix(allocator, std::span(reinterpret_cast<const std::byte*>(source.data()), source.size())),
        std::length_error,
        [](const std::length_error& e) {
            BOOST_REQUIRE_EQUAL(e.what(), "maximum capacity reached");
            return true;
        });
    BOOST_REQUIRE_EQUAL(0, allocator.Length());
    BOOST_REQUIRE_EQUAL(0, allocator.Capacity());
}

std::vector<std::tuple<std::string, size_t>> DecodeNumberTestData = {
    {std::string("\x00", 1), 0},
    {std::string("\x01", 1), 1},
    {std::string("\x7F", 1), 127},
    {std::string("\x80\x00\x00\x80", 4), 128},
    {std::string("\x80\x00\xFF\xFF", 4), 65535},
    {std::string("\x80\x01\x00\x00", 4), 65536},
};

BOOST_DATA_TEST_CASE(DecodeNumberWithSpanReferenceTest, DecodeNumberTestData, buffer, number) {
    std::span<const std::byte> source(reinterpret_cast<const std::byte*>(buffer.data()), buffer.size());
    size_t actual = ::binary::Decode(source);
    BOOST_REQUIRE_EQUAL(0, source.size());
    BOOST_REQUIRE_EQUAL(number, actual);
}

BOOST_DATA_TEST_CASE(DecodeNumberWithSpanValueOutputBytesReadTest, DecodeNumberTestData, buffer, number) {
    const std::span<const std::byte> source(reinterpret_cast<const std::byte*>(buffer.data()), buffer.size());
    size_t bytesRead;
    size_t actual = ::binary::Decode(source, bytesRead);
    BOOST_REQUIRE_EQUAL(buffer.size(), source.size());
    BOOST_REQUIRE_EQUAL(buffer.size(), bytesRead);
    BOOST_REQUIRE_EQUAL(number, actual);
}

std::vector<std::tuple<std::string>> DecodeNumberInvalidBytesTestData = {
    {std::string("", 0)},
    {std::string("\x80", 1)},
    {std::string("\x80\x00", 2)},
    {std::string("\x80\x00\x00", 3)},
};

BOOST_DATA_TEST_CASE(DecodeNumberWithSpanReferenceInvalidBytesTest, DecodeNumberInvalidBytesTestData, buffer) {
    std::span<const std::byte> source(reinterpret_cast<const std::byte*>(buffer.data()), buffer.size());
    BOOST_REQUIRE_EXCEPTION(
        ::binary::Decode(source),
        std::length_error,
        [](const std::length_error& e) {
            BOOST_REQUIRE_EQUAL(e.what(), "not enough bytes or byte sequence invalid");
            return true;
        });
    BOOST_REQUIRE_EQUAL(buffer.size(), source.size());
}

BOOST_DATA_TEST_CASE(DecodeNumberWithSpanValueOutputBytesReadInvalidBytesTest, DecodeNumberInvalidBytesTestData, buffer) {
    const std::span<const std::byte> source(reinterpret_cast<const std::byte*>(buffer.data()), buffer.size());
    size_t bytesRead = 0;
    BOOST_REQUIRE_EXCEPTION(
        ::binary::Decode(source, bytesRead),
        std::length_error,
        [](const std::length_error& e) {
            BOOST_REQUIRE_EQUAL(e.what(), "not enough bytes or byte sequence invalid");
            return true;
        });
    BOOST_REQUIRE_EQUAL(buffer.size(), source.size());
    BOOST_REQUIRE_EQUAL(0, bytesRead);
}

std::vector<std::tuple<std::string, size_t>> DecodeWithLengthPrefixTestData = {
    {std::string("\x00", 1), 0},
    {std::string("\x01\x00", 2), 1},
    {std::string("\x02\x00\x00", 3), 2},
    {std::string("\x80\x00\x00\x00", 4), 0},
    {std::string("\x80\x00\x00\x01\x00", 5), 1},
    {std::string("\x80\x00\x00\x02\x00\x00", 6), 2},
};

BOOST_DATA_TEST_CASE(DecodeWithLengthPrefixTest, DecodeWithLengthPrefixTestData, buffer, length) {
    std::span<const std::byte> source(reinterpret_cast<const std::byte*>(buffer.data()), buffer.size());
    auto actual = ::binary::DecodeWithLengthPrefix(source);
    BOOST_REQUIRE_EQUAL(source.size(), 0);
    BOOST_REQUIRE_EQUAL(actual.size(), length);
}

BOOST_AUTO_TEST_SUITE_END()
}
