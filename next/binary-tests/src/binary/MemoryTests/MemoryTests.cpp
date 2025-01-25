#include <boost/test/data/test_case.hpp>
#include <boost/test/unit_test.hpp>

#include <binary/Allocator.hpp>
#include <binary/Memory.hpp>

#include <array>

namespace tests::binary::MemoryTests {
BOOST_AUTO_TEST_SUITE(MemoryTests)

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
}

BOOST_DATA_TEST_CASE(EncodeNumberWithSpanValueTest, EncodeNumberTestData, number, buffer) {
    std::array<std::byte, 16> target;
    size_t bytesWritten;
    ::binary::Encode(target, number, bytesWritten);
    BOOST_REQUIRE_EQUAL(buffer.size(), bytesWritten);
    BOOST_REQUIRE_EQUAL(buffer, std::string(reinterpret_cast<const char*>(target.data()), bytesWritten));
}

BOOST_DATA_TEST_CASE(EncodeNumberWithSpanValueInvalidNumberTest, boost::unit_test::data::make<size_t>({static_cast<uint32_t>(INT32_MAX) + 1, UINT32_MAX}), number) {
    std::array<std::byte, 16> target;
    size_t bytesWritten;
    BOOST_REQUIRE_EXCEPTION(
        ::binary::Encode(target, number, bytesWritten),
        std::invalid_argument,
        [](const std::invalid_argument& e) {
            BOOST_REQUIRE_EQUAL(e.what(), "number > INT32_MAX");
            return true;
        });
}

BOOST_DATA_TEST_CASE(EncodeNumberWithSpanValueNotEnoughBytesToWriteTest, EncodeNumberTestData, number, buffer) {
    std::array<std::byte, 16> values;
    std::span<std::byte> target(values.data(), buffer.size() - 1);
    size_t bytesWritten;
    BOOST_REQUIRE_EXCEPTION(
        ::binary::Encode(target, number, bytesWritten),
        std::length_error,
        [](const std::length_error& e) {
            BOOST_REQUIRE_EQUAL(e.what(), "not enough bytes to write");
            return true;
        });
}

BOOST_AUTO_TEST_SUITE_END()
}
