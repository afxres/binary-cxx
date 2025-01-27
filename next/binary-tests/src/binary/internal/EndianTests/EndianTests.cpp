#include <boost/test/data/test_case.hpp>
#include <boost/test/unit_test.hpp>

#include <binary/internal/Endian.hpp>

#include <array>

namespace tests::binary::internal::EndianTests {
BOOST_AUTO_TEST_SUITE(EndianTests)

std::vector<std::tuple<uint16_t, std::string>> EndianI16TestData = {
    {0x1234, std::string("\x34\x12", 2)},
    {0xABCD, std::string("\xCD\xAB", 2)},
};

BOOST_DATA_TEST_CASE(EndianI16Test, EndianI16TestData, number, buffer) {
    std::array<char, 2> big;
    std::array<char, 2> little;
    ::binary::internal::EncodeBigEndian(big.data(), number);
    ::binary::internal::EncodeLittleEndian(little.data(), number);
    BOOST_REQUIRE_EQUAL(std::string(big.data(), big.size()), std::string(buffer.rbegin(), buffer.rend()));
    BOOST_REQUIRE_EQUAL(std::string(little.data(), little.size()), buffer);
}

std::vector<std::tuple<uint32_t, std::string>> EndianI32TestData = {
    {0x12345678, std::string("\x78\x56\x34\x12", 4)},
    {0x89ABCDEF, std::string("\xEF\xCD\xAB\x89", 4)},
};

BOOST_DATA_TEST_CASE(EndianI32Test, EndianI32TestData, number, buffer) {
    std::array<char, 4> big;
    std::array<char, 4> little;
    ::binary::internal::EncodeBigEndian(big.data(), number);
    ::binary::internal::EncodeLittleEndian(little.data(), number);
    BOOST_REQUIRE_EQUAL(std::string(big.data(), big.size()), std::string(buffer.rbegin(), buffer.rend()));
    BOOST_REQUIRE_EQUAL(std::string(little.data(), little.size()), buffer);
}

std::vector<std::tuple<uint64_t, std::string>> EndianI64TestData = {
    {0x0123456789ABCDEF, std::string("\xEF\xCD\xAB\x89\x67\x45\x23\x01", 8)},
    {0xFEDCBA9876543210, std::string("\x10\x32\x54\x76\x98\xBA\xDC\xFE", 8)},
};

BOOST_DATA_TEST_CASE(EndianI64Test, EndianI64TestData, number, buffer) {
    std::array<char, 8> big;
    std::array<char, 8> little;
    ::binary::internal::EncodeBigEndian(big.data(), number);
    ::binary::internal::EncodeLittleEndian(little.data(), number);
    BOOST_REQUIRE_EQUAL(std::string(big.data(), big.size()), std::string(buffer.rbegin(), buffer.rend()));
    BOOST_REQUIRE_EQUAL(std::string(little.data(), little.size()), buffer);
}

BOOST_AUTO_TEST_SUITE_END()
}
