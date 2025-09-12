#include <boost/mpl/list.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/unit_test.hpp>

#include <binary/experimental/converters/LittleEndianConverter.hpp>

#include <array>

namespace tests::binary::experimental::converters::LittleEndianConverterTests {
BOOST_AUTO_TEST_SUITE(LittleEndianConverterTests)

using LittleEndianConverterTestTypeData = boost::mpl::list<int8_t, int16_t, int32_t, int64_t>;

BOOST_AUTO_TEST_CASE_TEMPLATE(LittleEndianConverterLengthTest, T, LittleEndianConverterTestTypeData) {
    BOOST_REQUIRE_EQUAL(sizeof(T), ::binary::experimental::converters::LittleEndianConverter<T>::Length());
    BOOST_REQUIRE_EQUAL(sizeof(T), ::binary::experimental::Converter<T>::Length());
}

template <typename T>
void TestAllMethods(const T& item) {
    auto x = ::binary::Allocator::Invoke([item](auto& allocator) { ::binary::experimental::converters::LittleEndianConverter<T>::Encode(allocator, item); });
    auto y = ::binary::Allocator::Invoke([item](auto& allocator) { ::binary::experimental::Converter<T>::Encode(allocator, item); });
    BOOST_REQUIRE_EQUAL(sizeof(T), x.size());
    BOOST_REQUIRE_EQUAL(sizeof(T), y.size());
    auto p = ::binary::experimental::converters::LittleEndianConverter<T>::Decode(x);
    auto q = ::binary::experimental::Converter<T>::Decode(x);
    BOOST_REQUIRE_EQUAL(item, p);
    BOOST_REQUIRE_EQUAL(item, q);
}

template <typename T>
void TestAll(const std::vector<T>& container, std::function<void(const T&)> action) {
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
    BOOST_REQUIRE_EXCEPTION(
        ::binary::experimental::converters::LittleEndianConverter<T>::Decode(buffer),
        std::length_error,
        [](const std::length_error& e) {
            BOOST_REQUIRE_EQUAL(e.what(), "not enough bytes or byte sequence invalid");
            return true;
        });
    BOOST_REQUIRE_EXCEPTION(
        ::binary::experimental::Converter<T>::Decode(buffer),
        std::length_error,
        [](const std::length_error& e) {
            BOOST_REQUIRE_EQUAL(e.what(), "not enough bytes or byte sequence invalid");
            return true;
        });
}

BOOST_AUTO_TEST_SUITE_END()
}
