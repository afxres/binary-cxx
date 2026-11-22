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

#if defined(BINARY_HAS_INT128)
__extension__ using Int128 = __int128;

BOOST_AUTO_TEST_CASE(EndianI128Test) {
    const auto value = static_cast<Int128>(0x0123456789ABCDEF);
    std::array<char, 16> little;
    ::binary::internal::EncodeLittleEndian(little.data(), value);
    const std::string expected("\xEF\xCD\xAB\x89\x67\x45\x23\x01\x00\x00\x00\x00\x00\x00\x00\x00", 16);
    BOOST_REQUIRE(std::string(little.data(), little.size()) == expected);
    const auto roundtrip = ::binary::internal::DecodeLittleEndian<Int128>(little.data());
    BOOST_REQUIRE(roundtrip == value);
}

BOOST_AUTO_TEST_CASE(EndianI128BigTest) {
    const auto value = static_cast<Int128>(0x0123456789ABCDEF);
    std::array<char, 16> big;
    ::binary::internal::EncodeBigEndian(big.data(), value);
    const std::string expected("\x00\x00\x00\x00\x00\x00\x00\x00\x01\x23\x45\x67\x89\xAB\xCD\xEF", 16);
    BOOST_REQUIRE(std::string(big.data(), big.size()) == expected);
    const auto roundtrip = ::binary::internal::DecodeBigEndian<Int128>(big.data());
    BOOST_REQUIRE(roundtrip == value);
}
#endif

BOOST_AUTO_TEST_SUITE_END()
}
