#include <boost/test/data/test_case.hpp>
#include <boost/test/unit_test.hpp>

#include <binary/external/BinaryObject.hpp>

namespace tests::binary::HashCodeListTests {
BOOST_AUTO_TEST_SUITE(HashCodeListTest)

BOOST_AUTO_TEST_CASE(HashCodeListInvokeTest) {
    std::vector<std::string> values;
    for (size_t i = 0; i < 32; i++) {
        auto source = std::to_string(i);
        auto result = std::string();
        for (size_t k = 0; k < i; k++) {
            result += source;
        }
        values.emplace_back(result);
    }
    std::vector<std::vector<std::byte>> target;
    for (const auto& i : values) {
        auto data = reinterpret_cast<const std::byte*>(i.data());
        target.emplace_back(std::vector<std::byte>(data, data + i.size()));
    }
    auto [code, list] = ::binary::external::CreateHashCodeList(target);
    BOOST_REQUIRE_EQUAL(code, SIZE_MAX);
    BOOST_REQUIRE_NE(list, nullptr);

    for (size_t i = 0; i < values.size(); i++) {
        auto data = reinterpret_cast<const std::byte*>(values.at(i).data());
        auto item = list->Invoke({data, values.at(i).size()});
        BOOST_REQUIRE_EQUAL(item, i);
    }
}

BOOST_AUTO_TEST_CASE(HashCodeListInvokeNotFoundTest) {
    std::vector<std::string> values{
        "A",
        "C",
    };
    std::vector<std::vector<std::byte>> target;
    for (const auto& i : values) {
        auto data = reinterpret_cast<const std::byte*>(i.data());
        target.emplace_back(std::vector<std::byte>(data, data + i.size()));
    }
    auto [code, list] = ::binary::external::CreateHashCodeList(target);
    BOOST_REQUIRE_EQUAL(code, SIZE_MAX);
    BOOST_REQUIRE_NE(list, nullptr);

    BOOST_REQUIRE_EQUAL(list->Invoke(std::vector<std::byte>({static_cast<std::byte>('A')})), 0);
    BOOST_REQUIRE_EQUAL(list->Invoke(std::vector<std::byte>({static_cast<std::byte>('C')})), 1);
    BOOST_REQUIRE_EQUAL(list->Invoke(std::vector<std::byte>({static_cast<std::byte>('B')})), SIZE_MAX);
}

BOOST_AUTO_TEST_SUITE_END()
}
