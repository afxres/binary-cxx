#include <boost/mpl/list.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/unit_test.hpp>

#include <binary/Generator.hpp>
#include <binary/GeneratorExtensions.hpp>
#include <binary/converters/ContainerConverter.hpp>
#include <binary/converters/LittleEndianConverter.hpp>
#include <binary/converters/LittleEndianStringConverter.hpp>
#include <binary/converters/TupleConverter.hpp>

#include <binary/experimental/Converter.hpp>

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

::binary::Generator GetGenerator() {
    ::binary::Generator generator;
    ::binary::AddConverter<::binary::converters::LittleEndianConverter<int32_t>>(generator);
    ::binary::AddConverter<::binary::converters::LittleEndianConverter<double>>(generator);
    ::binary::AddConverter<::binary::converters::LittleEndianStringConverter<std::string>>(generator);
    ::binary::AddConverter<::binary::converters::ContainerConverter<std::vector<std::string>>>(generator);
    ::binary::AddConverter<::binary::converters::TupleConverter<Point>>(generator);
    ::binary::AddConverter<::binary::converters::TupleConverter<Circle>>(generator);
    ::binary::AddConverter<::binary::converters::TupleConverter<Object>>(generator);
    ::binary::AddConverter<::binary::converters::TupleConverter<Weapon>>(generator);
    return generator;
}

BOOST_AUTO_TEST_CASE_TEMPLATE(ContantLengthStructureTypeTupleConverterLengthTest, T, ConstantLengthStructureTypeTupleConverterTestTypeData) {
    auto generator = GetGenerator();
    auto converter = ::binary::GetConverter<T>(generator);
    BOOST_REQUIRE_EQUAL(typeid(::binary::converters::TupleConverter<T>).name(), typeid(*converter).name());
    BOOST_REQUIRE_NE(0, converter->Length());

    using ConverterType = ::binary::experimental::Converter<T>;
    std::string name = typeid(ConverterType).name();
    BOOST_REQUIRE(name.find("experimental") != 0);
    BOOST_REQUIRE(name.find("TupleConverter") != 0);
    BOOST_REQUIRE_NE(0, ConverterType::Length());
    BOOST_REQUIRE_EQUAL(converter->Length(), ConverterType::Length());
}

BOOST_AUTO_TEST_CASE_TEMPLATE(VariableLengthStructureTypeTupleConverterLengthTest, T, VariableLengthStructureTypeTupleConverterTestTypeData) {
    auto generator = GetGenerator();
    auto converter = ::binary::GetConverter<T>(generator);
    BOOST_REQUIRE_EQUAL(typeid(::binary::converters::TupleConverter<T>).name(), typeid(*converter).name());
    BOOST_REQUIRE_EQUAL(0, converter->Length());

    using ConverterType = ::binary::experimental::Converter<T>;
    std::string name = typeid(ConverterType).name();
    BOOST_REQUIRE(name.find("experimental") != 0);
    BOOST_REQUIRE(name.find("TupleConverter") != 0);
    BOOST_REQUIRE_EQUAL(0, ConverterType::Length());
    BOOST_REQUIRE_EQUAL(converter->Length(), ConverterType::Length());
}

template <typename T>
void TestAllMethods(const T& source) {
    auto generator = GetGenerator();
    auto converter = ::binary::GetConverter<T>(generator);
    auto dataBufferOrigin = ::binary::Allocator::Invoke([&source, &converter](auto& allocator) { converter->Encode(allocator, source); });
    auto autoBufferOrigin = ::binary::Allocator::Invoke([&source, &converter](auto& allocator) { converter->EncodeAuto(allocator, source); });
    BOOST_REQUIRE_EQUAL(dataBufferOrigin.size() == autoBufferOrigin.size(), converter->Length() != 0);

    using ConverterType = ::binary::experimental::Converter<T>;
    auto dataBuffer = ::binary::Allocator::Invoke([&source](auto& allocator) { ConverterType::Encode(allocator, source); });
    auto autoBuffer = ::binary::Allocator::Invoke([&source](auto& allocator) { ConverterType::EncodeAuto(allocator, source); });
    BOOST_REQUIRE_EQUAL(dataBuffer.size() == autoBuffer.size(), ConverterType::Length() != 0);
    BOOST_REQUIRE_EQUAL(std::string_view(reinterpret_cast<const char*>(dataBufferOrigin.data()), dataBufferOrigin.size()), std::string_view(reinterpret_cast<const char*>(dataBuffer.data()), dataBuffer.size()));
    BOOST_REQUIRE_EQUAL(std::string_view(reinterpret_cast<const char*>(autoBufferOrigin.data()), autoBufferOrigin.size()), std::string_view(reinterpret_cast<const char*>(autoBuffer.data()), autoBuffer.size()));

    std::span<const std::byte> dataSpanOrigin(dataBufferOrigin);
    std::span<const std::byte> autoSpanOrigin(autoBufferOrigin);
    auto dataResultOrigin = converter->Decode(dataSpanOrigin);
    auto autoResultOrigin = converter->DecodeAuto(autoSpanOrigin);
    BOOST_REQUIRE(source == dataResultOrigin);
    BOOST_REQUIRE(source == autoResultOrigin);
    BOOST_REQUIRE_EQUAL(dataSpanOrigin.size(), dataBufferOrigin.size());
    BOOST_REQUIRE_EQUAL(autoSpanOrigin.size(), 0);

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
