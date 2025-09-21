#include <boost/test/data/test_case.hpp>
#include <boost/test/unit_test.hpp>

#include <binary/external/BinaryObject.hpp>

namespace tests::binary::BinaryObjectTests {
BOOST_AUTO_TEST_SUITE(BinaryObjectTest)

BOOST_AUTO_TEST_CASE(ByteViewListCreateWithManyItemsTest) {
    std::vector<std::string> values;
    for (size_t i = 0; i < 100; i++) {
        values.emplace_back(std::to_string(i));
    }
    std::vector<std::vector<std::byte>> target;
    for (const auto& i : values) {
        auto data = reinterpret_cast<const std::byte*>(i.data());
        target.emplace_back(std::vector<std::byte>(data, data + i.size()));
    }
    auto [code, list] = ::binary::external::CreateByteViewList(target);
    BOOST_REQUIRE_EQUAL(code, SIZE_MAX);
    BOOST_REQUIRE_EQUAL(dynamic_cast<::binary::external::LongDataList*>(list.get()), nullptr);
    BOOST_REQUIRE_NE(dynamic_cast<::binary::external::HashCodeList*>(list.get()), nullptr);
}

BOOST_AUTO_TEST_CASE(ByteViewListCreateWithLongValueTest) {
    std::vector<std::string> values{
        std::string(20, 'A'),
    };
    std::vector<std::vector<std::byte>> target;
    for (const auto& i : values) {
        auto data = reinterpret_cast<const std::byte*>(i.data());
        target.emplace_back(std::vector<std::byte>(data, data + i.size()));
    }
    auto [code, list] = ::binary::external::CreateByteViewList(target);
    BOOST_REQUIRE_EQUAL(code, SIZE_MAX);
    BOOST_REQUIRE_EQUAL(dynamic_cast<::binary::external::LongDataList*>(list.get()), nullptr);
    BOOST_REQUIRE_NE(dynamic_cast<::binary::external::HashCodeList*>(list.get()), nullptr);
}

BOOST_AUTO_TEST_CASE(LongDataListCreateWithSameItemTest) {
    std::vector<std::string> values{
        "1",
        "2",
        "2",
    };
    std::vector<std::vector<std::byte>> target;
    for (const auto& i : values) {
        auto data = reinterpret_cast<const std::byte*>(i.data());
        target.emplace_back(std::vector<std::byte>(data, data + i.size()));
    }
    auto [code, list] = ::binary::external::CreateLongDataList(target);
    BOOST_REQUIRE_EQUAL(code, 2);
    BOOST_REQUIRE_EQUAL(list, nullptr);
}

BOOST_AUTO_TEST_CASE(HashCodeListCreateWithSameItemTest) {
    std::vector<std::string> values{
        "A",
        "B",
        "C",
        "B",
    };
    std::vector<std::vector<std::byte>> target;
    for (const auto& i : values) {
        auto data = reinterpret_cast<const std::byte*>(i.data());
        target.emplace_back(std::vector<std::byte>(data, data + i.size()));
    }
    auto [code, list] = ::binary::external::CreateHashCodeList(target);
    BOOST_REQUIRE_EQUAL(code, 3);
    BOOST_REQUIRE_EQUAL(list, nullptr);
}

BOOST_AUTO_TEST_SUITE_END()
}
