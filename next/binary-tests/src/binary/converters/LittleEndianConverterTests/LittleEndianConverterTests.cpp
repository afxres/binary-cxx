#include <boost/mpl/list.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/unit_test.hpp>

#include <binary/converters/LittleEndianConverter.hpp>

namespace tests::binary::converters::LittleEndianConverterTests {
BOOST_AUTO_TEST_SUITE(LittleEndianConverterTests)

using ::binary::Allocator;
using ::binary::converters::LittleEndianConverter;
using LittleEndianConverterTestTypeData = boost::mpl::list<int8_t, int16_t, int32_t, int64_t>;

BOOST_AUTO_TEST_CASE_TEMPLATE(LittleEndianConverterLengthTest, T, LittleEndianConverterTestTypeData) {
    auto a = LittleEndianConverter<std::add_const_t<T>>();
    auto b = LittleEndianConverter<std::remove_const_t<T>>();
    BOOST_REQUIRE_EQUAL(a.Length(), sizeof(T));
    BOOST_REQUIRE_EQUAL(b.Length(), sizeof(T));
}

template <typename T>
void TestAllMethods(const T& item) {
    auto a = LittleEndianConverter<std::add_const_t<T>>();
    auto b = LittleEndianConverter<std::remove_const_t<T>>();
    auto x = Allocator::Invoke([&a, item](auto& allocator) { a.Encode(allocator, item); });
    auto y = Allocator::Invoke([&a, item](auto& allocator) { a.Encode(allocator, item); });
    BOOST_REQUIRE_EQUAL(sizeof(T), x.size());
    BOOST_REQUIRE_EQUAL(sizeof(T), y.size());
    auto p = a.Decode(x);
    auto q = b.Decode(y);
    BOOST_REQUIRE_EQUAL(item, p);
    BOOST_REQUIRE_EQUAL(item, q);
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
