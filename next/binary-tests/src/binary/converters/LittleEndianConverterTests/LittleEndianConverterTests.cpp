#include <boost/mpl/list.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/unit_test.hpp>

#include <binary/converters/LittleEndianConverter.hpp>

namespace binary::converters::tests::LittleEndianConverterTests {
BOOST_AUTO_TEST_SUITE(LittleEndianConverterTests)

using LittleEndianConverterLengthData = boost::mpl::list<int8_t, int16_t, int32_t, int64_t>;

BOOST_AUTO_TEST_CASE_TEMPLATE(LittleEndianConverterLengthTest, T, LittleEndianConverterLengthData) {
    LittleEndianConverter<T> converter;
    BOOST_REQUIRE_EQUAL(converter.Length(), sizeof(T));
}

template <typename T>
void TestEncodeDecodeMethods(const T& item) {
    Allocator allocator;
    LittleEndianConverter<T> converter;
    converter.Encode(allocator, item);
    BOOST_REQUIRE_EQUAL(allocator.Length(), sizeof(T));
    T result = converter.Decode(allocator.AsSpan());
    BOOST_REQUIRE_EQUAL(result, item);
}

template <typename T>
void TestEncodeAutoDecodeAutoMethods(const T& item) {
    Allocator allocator;
    LittleEndianConverter<T> converter;
    converter.EncodeAuto(allocator, item);
    BOOST_REQUIRE_EQUAL(allocator.Length(), sizeof(T));
    std::span<std::byte> memory = allocator.AsSpan();
    T result = converter.DecodeAuto(memory);
    BOOST_REQUIRE_EQUAL(memory.size(), 0);
    BOOST_REQUIRE_EQUAL(result, item);
}

template <typename T>
void TestAllMethods(const T& item) {
    TestEncodeDecodeMethods<T>(item);
    TestEncodeAutoDecodeAutoMethods<T>(item);
}

template <typename T>
void TestAll(const std::vector<T>& collection, std::function<void(const T&)> action) {
    for (const T& i : collection) {
        action(i);
    }
}

BOOST_AUTO_TEST_CASE(LittleEndianConverterEncodeDecodeIntegrationTest) {
    TestAll<int32_t>({-100, 0, 1, 65537}, TestAllMethods<int32_t>);
    TestAll<int64_t>({INT64_MIN, 0, 1, INT64_MAX}, TestAllMethods<int64_t>);
}

BOOST_AUTO_TEST_SUITE_END()
}
