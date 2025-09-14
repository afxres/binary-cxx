#include <boost/mpl/list.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/unit_test.hpp>

#include <binary/experimental/converters/ContainerConverter.hpp>
#include <binary/experimental/converters/LittleEndianConverter.hpp>
#include <binary/experimental/converters/LittleEndianStringConverter.hpp>
#include <binary/experimental/converters/TupleConverter.hpp>

namespace tests::binary::experimental::converters::TupleConverterTests {
BOOST_AUTO_TEST_SUITE(StructureTypeTupleConverterTests)

struct Point {
    double x;
    double y;
    bool operator==(const Point&) const = default;
};

struct Circle {
    Point point;
    double radius;
    bool operator==(const Circle&) const = default;
};

struct Object {
    int32_t id;
    std::string name;
    bool operator==(const Object&) const = default;
};

struct Weapon {
    Object object;
    std::vector<std::string> tags;
    bool operator==(const Weapon&) const = default;
};

std::vector<Circle> CircleData = {
    Circle{.point = Point{.x = 1, .y = 2}, .radius = 3},
    Circle{.point = Point{.x = 4, .y = 5}, .radius = 6},
};

std::vector<Weapon> WeaponData = {
    Weapon{.object = Object{.id = 1, .name = "HMG"}, .tags = {"heavy"}},
    Weapon{.object = Object{.id = 2, .name = "SMG"}, .tags = {"cheap", "light"}},
};

using ConstantLengthStructureTypeTupleConverterTestTypeData = boost::mpl::list<Point, Circle>;

using VariableLengthStructureTypeTupleConverterTestTypeData = boost::mpl::list<Object, Weapon>;

BOOST_AUTO_TEST_CASE_TEMPLATE(ContantLengthStructureTypeTupleConverterLengthTest, T, ConstantLengthStructureTypeTupleConverterTestTypeData) {
    using ConverterType = ::binary::experimental::Converter<T>;
    using ActualConverterType = typename ConverterType::ActualConverterType;
    std::string name = typeid(ActualConverterType).name();
    BOOST_REQUIRE(name.find("experimental") != 0);
    BOOST_REQUIRE(name.find("TupleConverter") != 0);
    BOOST_REQUIRE_NE(0, ConverterType::Length());
    BOOST_REQUIRE_NE(0, ActualConverterType::Length());
}

BOOST_AUTO_TEST_CASE_TEMPLATE(VariableLengthStructureTypeTupleConverterLengthTest, T, VariableLengthStructureTypeTupleConverterTestTypeData) {
    using ConverterType = ::binary::experimental::Converter<T>;
    using ActualConverterType = typename ConverterType::ActualConverterType;
    std::string name = typeid(ActualConverterType).name();
    BOOST_REQUIRE(name.find("experimental") != 0);
    BOOST_REQUIRE(name.find("TupleConverter") != 0);
    BOOST_REQUIRE_EQUAL(0, ConverterType::Length());
    BOOST_REQUIRE_EQUAL(0, ActualConverterType::Length());
}

template <typename T>
void TestAllMethods(const T& source) {
    using ConverterType = ::binary::experimental::Converter<T>;
    auto dataBuffer = ::binary::Allocator::Invoke([&source](auto& allocator) { ConverterType::Encode(allocator, source); });
    auto autoBuffer = ::binary::Allocator::Invoke([&source](auto& allocator) { ConverterType::EncodeAuto(allocator, source); });
    BOOST_REQUIRE_EQUAL(dataBuffer.size() == autoBuffer.size(), ConverterType::Length() != 0);

    std::span<const std::byte> dataSpan(dataBuffer);
    std::span<const std::byte> autoSpan(autoBuffer);
    auto dataResult = ConverterType::Decode(dataSpan);
    auto autoResult = ConverterType::DecodeAuto(autoSpan);
    BOOST_REQUIRE(source == dataResult);
    BOOST_REQUIRE(source == autoResult);
    BOOST_REQUIRE_EQUAL(dataSpan.size(), dataBuffer.size());
    BOOST_REQUIRE_EQUAL(autoSpan.size(), 0);
}

template <typename T>
void TestAll(const std::vector<T>& container, std::function<void(const T&)> action) {
    for (const T& i : container) {
        action(i);
    }
}

BOOST_AUTO_TEST_CASE(StructureTypeTupleConverterIntegrationTest) {
    TestAll<Circle>(CircleData, TestAllMethods<Circle>);
    TestAll<Weapon>(WeaponData, TestAllMethods<Weapon>);
}

BOOST_AUTO_TEST_SUITE_END()
}
