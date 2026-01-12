#include <boost/test/data/test_case.hpp>
#include <boost/test/unit_test.hpp>

#include <binary/internal/Length.hpp>

#include <array>

namespace tests::binary::internal::LengthTests {
BOOST_AUTO_TEST_SUITE(LengthTests)

BOOST_AUTO_TEST_CASE(EnsureMemoryAssertFailedTest) {
    BOOST_REQUIRE_EXCEPTION(
        ::binary::internal::EnsureMemoryAccess(nullptr),
        std::runtime_error,
        [](const std::runtime_error& e) {
            BOOST_REQUIRE_EQUAL(e.what(), "invalid memory access or out of memory");
            return true;
        });
}

std::vector<uint32_t> LengthPrefixTestNumberData = {
    0,
    1,
    127,
    128,
    INT32_MAX,
};

BOOST_DATA_TEST_CASE(EncodeDecodeLengthPrefixTest, LengthPrefixTestNumberData, source) {
    std::array<std::byte, 4> buffer;
    buffer.fill(static_cast<std::byte>(0));
    size_t numberLength = ::binary::internal::EncodeLengthPrefixLength(source);
    ::binary::internal::EncodeLengthPrefix(buffer.data(), source, numberLength);
    size_t offset = 0;
    size_t actual = ::binary::internal::DecodeLengthPrefix(buffer.data(), offset, buffer.size());
    BOOST_REQUIRE_EQUAL(actual, source);
    BOOST_REQUIRE_EQUAL(offset, numberLength);
}

BOOST_AUTO_TEST_SUITE_END()
}
