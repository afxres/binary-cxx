#include <boost/test/data/test_case.hpp>
#include <boost/test/unit_test.hpp>

#include <binary/Generator.hpp>
#include <binary/GeneratorExtensions.hpp>
#include <binary/components/TupleObject.hpp>
#include <binary/converters/LittleEndianConverter.hpp>
#include <binary/converters/LittleEndianStringConverter.hpp>

namespace tests::binary::components::TupleObjectTests {
BOOST_AUTO_TEST_SUITE(SimplePersonTupleObjectConverterTests)

struct SimplePerson {
    int8_t Age{};
    std::string Name;
};

class SimplePersonCustom {
public:
    auto GetAge() const { return this->age; }
    void SetAge(int8_t age) { this->age = age; }
    auto GetName() const { return this->name; }
    void SetName(std::string name) { this->name = name; }

private:
    int8_t age{};
    std::string name;
};

BINARY_TUPLE_OBJECT_CONVERTER(SimplePersonTupleObjectConverter, SimplePerson) {
    BINARY_TUPLE_MEMBER(Age);
    BINARY_TUPLE_MEMBER(Name);
}

BINARY_TUPLE_OBJECT_CONVERTER(SimplePersonCustomTupleObjectConverter, SimplePersonCustom) {
    BINARY_TUPLE_MEMBER_CUSTOM(item.GetAge(), item.SetAge(result), std::make_shared<::binary::converters::LittleEndianConverter<int8_t>>());
    BINARY_TUPLE_MEMBER_CUSTOM(item.GetName(), item.SetName(result), std::make_shared<::binary::converters::LittleEndianStringConverter<std::string>>());
}

BOOST_AUTO_TEST_CASE(SimplePersonTupleObjectConverterLengthTest) {
    ::binary::Generator generator;
    ::binary::AddConverter<::binary::converters::LittleEndianConverter<int8_t>>(generator);
    ::binary::AddConverter<::binary::converters::LittleEndianStringConverter<std::string>>(generator);
    ::binary::AddConverter<SimplePersonTupleObjectConverter>(generator);
    ::binary::AddConverter<SimplePersonCustomTupleObjectConverter>(generator);
    auto a = ::binary::GetConverter<SimplePerson>(generator);
    auto b = ::binary::GetConverter<SimplePersonCustom>(generator);
    BOOST_REQUIRE_EQUAL(typeid(SimplePersonTupleObjectConverter).name(), typeid(*a).name());
    BOOST_REQUIRE_EQUAL(typeid(SimplePersonCustomTupleObjectConverter).name(), typeid(*b).name());
    BOOST_REQUIRE_EQUAL(0, a->Length());
    BOOST_REQUIRE_EQUAL(0, b->Length());
}

std::vector<std::tuple<int8_t, std::string, int32_t>> SimplePersonTestData = {
    {18, "Alice", 6},
    {20, "Bob", 4},
};

BOOST_DATA_TEST_CASE(SimplePersonConverterEncodeDecodeTest, SimplePersonTestData, age, name, outputLength) {
    ::binary::Generator generator;
    ::binary::AddConverter<::binary::converters::LittleEndianConverter<int8_t>>(generator);
    ::binary::AddConverter<::binary::converters::LittleEndianStringConverter<std::string>>(generator);
    ::binary::AddConverter<SimplePersonTupleObjectConverter>(generator);
    ::binary::AddConverter<SimplePersonCustomTupleObjectConverter>(generator);
    auto a = ::binary::GetConverter<SimplePerson>(generator);
    auto b = ::binary::GetConverter<SimplePersonCustom>(generator);
    SimplePerson x;
    x.Age = age;
    x.Name = name;
    SimplePersonCustom y;
    y.SetAge(age);
    y.SetName(name);
    auto f = ::binary::Allocator::Invoke([&a, &x](auto& allocator) { a->Encode(allocator, x); });
    auto g = ::binary::Allocator::Invoke([&b, &y](auto& allocator) { b->Encode(allocator, y); });
    BOOST_REQUIRE_EQUAL(std::string_view(reinterpret_cast<const char*>(f.data()), f.size()), std::string_view(reinterpret_cast<const char*>(g.data()), g.size()));
    BOOST_REQUIRE_EQUAL(f.size(), outputLength);
    BOOST_REQUIRE_EQUAL(g.size(), outputLength);

    auto z = a->Decode(std::span(f.data(), f.size()));
    auto w = b->Decode(std::span(g.data(), g.size()));
    BOOST_REQUIRE_EQUAL(age, z.Age);
    BOOST_REQUIRE_EQUAL(name, z.Name);
    BOOST_REQUIRE_EQUAL(age, w.GetAge());
    BOOST_REQUIRE_EQUAL(name, w.GetName());
}

BOOST_AUTO_TEST_SUITE_END()
}
