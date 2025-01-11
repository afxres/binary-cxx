#include <boost/test/data/test_case.hpp>
#include <boost/test/unit_test.hpp>

#include <binary/Generator.hpp>
#include <binary/GeneratorExtensions.hpp>
#include <binary/components/NamedObject.hpp>
#include <binary/converters/LittleEndianConverter.hpp>
#include <binary/converters/StringConverter.hpp>

namespace tests::binary::components::NamedObjectTests {
BOOST_AUTO_TEST_SUITE(SimplePersonNamedObjectConverterTests)

struct SimplePerson {
    int8_t age{};
    std::string name;
};

BINARY_NAMED_OBJECT_CONVERTER(SimplePerson, SimplePersonConverter)
BINARY_NAMED_MEMBER(age)
BINARY_NAMED_MEMBER(name)
BINARY_NAMED_OBJECT_CONVERTER_END()

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
    {18, "Alice", 17},
    {20, "Bob", 15},
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

std::vector<std::tuple<std::string, std::string>> SimplePersonDecodeKeyNotFoundTestData = {
    {std::string() + "\x03" + "age\x01\x10", "name"},
    {std::string() + "\x04" + "name\x05" + "Alice", "age"},
};

BOOST_DATA_TEST_CASE(SimplePersonDecodeKeyNotFoundTest, SimplePersonDecodeKeyNotFoundTestData, buffer, keyNotFound) {
    std::span<const std::byte> span(reinterpret_cast<const std::byte*>(buffer.data()), buffer.size());
    std::string output = "named key '" + keyNotFound + "' does not exist";
    ::binary::Generator generator;
    ::binary::AddConverter<::binary::converters::LittleEndianConverter<int8_t>>(generator);
    ::binary::AddConverter<::binary::converters::StringConverter>(generator);
    ::binary::AddConverter<SimplePersonConverter>(generator);
    auto converter = ::binary::GetConverter<SimplePerson>(generator);
    BOOST_REQUIRE_EXCEPTION(
        converter->Decode(span),
        std::invalid_argument,
        ([output](const std::invalid_argument& e) {
            BOOST_REQUIRE_EQUAL(e.what(), output);
            return true;
        }));
}

BOOST_AUTO_TEST_SUITE_END()
}
