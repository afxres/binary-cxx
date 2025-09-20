#include <boost/mpl/list.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/unit_test.hpp>

#include <binary/converters/LittleEndianConverter.hpp>

#include <array>

namespace tests::binary::converters::LittleEndianConverterTests {
BOOST_AUTO_TEST_SUITE(LittleEndianConverterTests)

using ::binary::Allocator;
using ::binary::converters::LittleEndianConverter;
using LittleEndianConverterTestTypeData = boost::mpl::list<int8_t, int16_t, int32_t, int64_t>;

BOOST_AUTO_TEST_CASE_TEMPLATE(LittleEndianConverterLengthTest, T, LittleEndianConverterTestTypeData) {
    auto a = LittleEndianConverter<T>();
    BOOST_REQUIRE_EQUAL(a.Length(), sizeof(T));
}

template <typename T>
void TestAllMethods(const T& item) {
    auto a = LittleEndianConverter<T>();
    auto x = Allocator::Invoke([&a, item](auto& allocator) { a.Encode(allocator, item); });
    BOOST_REQUIRE_EQUAL(sizeof(T), x.size());
    auto p = a.Decode(x);
    BOOST_REQUIRE_EQUAL(item, p);
}

template <typename T>
void TestAll(const std::vector<T>& container, const std::function<void(const T&)>& action) {
    for (const T& i : container) {
        action(i);
    }
}

BOOST_AUTO_TEST_CASE(LittleEndianConverterEncodeDecodeIntegrationTest) {
    TestAll<int32_t>({-100, 0, 1, 65537}, TestAllMethods<int32_t>);
    TestAll<int64_t>({INT64_MIN, 0, 1, INT64_MAX}, TestAllMethods<int64_t>);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(LittleEndianConverterDecodeNotEnoughBytesTest, T, LittleEndianConverterTestTypeData) {
    std::array<std::byte, sizeof(T) - 1> buffer;
    auto a = LittleEndianConverter<T>();
    BOOST_REQUIRE_EXCEPTION(
        a.Decode(buffer),
        std::length_error,
        [](const std::length_error& e) {
            BOOST_REQUIRE_EQUAL(e.what(), "not enough bytes or byte sequence invalid");
            return true;
        });
}

BOOST_AUTO_TEST_SUITE_END()
}
