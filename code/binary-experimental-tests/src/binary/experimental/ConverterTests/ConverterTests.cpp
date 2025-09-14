#include <boost/mpl/list.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/unit_test.hpp>

#include <binary/experimental/Converter.hpp>

namespace tests::binary::experimental::ConverterTests {
BOOST_AUTO_TEST_SUITE(ConverterTests)

enum class ObjectKind {
    None,
    Person,
};

struct Object {
    int32_t id;
    std::string name;
    ObjectKind kind;
    bool operator==(const Object&) const = default;
};

struct Entity {
    int64_t key;
    std::unordered_map<std::string, Object> instances;
    bool operator==(const Entity&) const = default;
};

using ConverterIntegrationTestTypeData = boost::mpl::list<
    int8_t, int16_t, int32_t, int64_t,
    std::string, std::wstring,
    std::tuple<int16_t, int32_t, int64_t>,
    std::pair<const int16_t, const int32_t>,
    std::variant<std::string, int32_t, int64_t>,
    std::variant<const int16_t, int32_t, const std::string>,
    std::vector<int32_t>, std::list<std::string>,
    std::map<int32_t, int64_t>, std::unordered_map<std::string, int64_t>,
    ObjectKind, Object, Entity>;

BOOST_AUTO_TEST_CASE_TEMPLATE(ConverterIntegrationTest, T, ConverterIntegrationTestTypeData) {
    auto source = T{};
    auto buffer = ::binary::experimental::Encode(source);
    const std::span<const std::byte> span = buffer;
    auto actual = ::binary::experimental::Decode<T>(span);
    BOOST_REQUIRE(source == actual);
}

BOOST_AUTO_TEST_SUITE_END()
}
