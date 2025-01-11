#include <boost/test/data/test_case.hpp>
#include <boost/test/unit_test.hpp>

#include <binary/Generator.hpp>
#include <binary/GeneratorExtensions.hpp>
#include <binary/components/TupleObject.hpp>
#include <binary/converters/LittleEndianConverter.hpp>
#include <binary/converters/StringConverter.hpp>

namespace tests::binary::components::TupleObjectTests {
BOOST_AUTO_TEST_SUITE(SimplePersonTupleObjectConverterTests)

struct SimplePerson {
    int8_t age{};
    std::string name;
};

BINARY_TUPLE_OBJECT_CONVERTER_BEGIN(SimplePerson, SimplePersonConverter)
BINARY_TUPLE_MEMBER(age)
BINARY_TUPLE_MEMBER(name)
BINARY_TUPLE_OBJECT_CONVERTER_END()

BOOST_AUTO_TEST_CASE(SimplePersonConverterLengthTest) {
    ::binary::Generator generator;
    ::binary::AddConverter<::binary::converters::LittleEndianConverter<int8_t>>(generator);
    ::binary::AddConverter<::binary::converters::StringConverter>(generator);
    ::binary::AddConverter<SimplePersonConverter>(generator);
    auto converter = ::binary::GetConverter<SimplePerson>(generator);
    BOOST_REQUIRE_EQUAL(typeid(SimplePersonConverter).name(), typeid(*converter).name());
    BOOST_REQUIRE_EQUAL(0, converter->Length());
}

std::vector<std::tuple<int8_t, std::string, int32_t>> SimplePersonTestData = {
    {18, "Alice", 6},
    {20, "Bob", 4},
};

BOOST_DATA_TEST_CASE(SimplePersonConverterEncodeDecodeTest, SimplePersonTestData, age, name, outputLength) {
    ::binary::Generator generator;
    ::binary::AddConverter<::binary::converters::LittleEndianConverter<int8_t>>(generator);
    ::binary::AddConverter<::binary::converters::StringConverter>(generator);
    ::binary::AddConverter<SimplePersonConverter>(generator);
    auto converter = ::binary::GetConverter<SimplePerson>(generator);
    SimplePerson person;
    person.age = age;
    person.name = name;
    ::binary::Allocator allocator;
    converter->Encode(allocator, person);
    BOOST_REQUIRE_EQUAL(allocator.Length(), outputLength);

    auto buffer = allocator.AsSpan();
    auto result = converter->Decode(buffer);
    BOOST_REQUIRE_EQUAL(age, result.age);
    BOOST_REQUIRE_EQUAL(name, result.name);
}

BOOST_AUTO_TEST_SUITE_END()
}
