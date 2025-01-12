#include <boost/test/data/test_case.hpp>
#include <boost/test/unit_test.hpp>

#include <binary/Generator.hpp>
#include <binary/GeneratorExtensions.hpp>
#include <binary/components/NamedObject.hpp>
#include <binary/converters/LittleEndianConverter.hpp>
#include <binary/converters/StringConverter.hpp>

namespace tests::binary::components::NamedObjectTests {
BOOST_AUTO_TEST_SUITE(SimplePersonNamedObjectConverterCustomTests)

class SimplePerson {
public:
    int8_t GetAge() const {
        return this->age;
    }

    std::string GetName() const {
        return this->name;
    }

    void SetAge(int8_t age) {
        this->age = age;
    }

    void SetName(std::string name) {
        this->name = name;
    }

private:
    int8_t age{};
    std::string name;
};

BINARY_NAMED_OBJECT_CONVERTER(SimplePerson, SimplePersonConverter)
BINARY_NAMED_MEMBER_CUSTOM("age", true, item.GetAge(), item.SetAge(result), std::make_shared<::binary::converters::LittleEndianConverter<int8_t>>())
BINARY_NAMED_MEMBER_CUSTOM("name", true, item.GetName(), item.SetName(result), std::make_shared<::binary::converters::StringConverter>())
BINARY_NAMED_OBJECT_CONVERTER_END()

BOOST_AUTO_TEST_CASE(SimplePersonConverterLengthTest) {
    ::binary::Generator generator;
    ::binary::AddConverter<::binary::converters::StringConverter>(generator);
    ::binary::AddConverter<SimplePersonConverter>(generator);
    auto converter = ::binary::GetConverter<SimplePerson>(generator);
    BOOST_REQUIRE_EQUAL(typeid(SimplePersonConverter).name(), typeid(*converter).name());
    BOOST_REQUIRE_EQUAL(0, converter->Length());
}

std::vector<std::tuple<std::string, int8_t, std::string>> SimplePersonDecodeOptionalMemberTestData = {
    {"", 0, ""},
    {std::string() + "\x03" + "age\x01\x12", 18, ""},
    {std::string() + "\x04" + "name\x05" + "Alice", 0, "Alice"},
};

BOOST_DATA_TEST_CASE(SimplePersonDecodeOptionalMemberTest, SimplePersonDecodeOptionalMemberTestData, buffer, age, name) {
    std::span<const std::byte> span(reinterpret_cast<const std::byte*>(buffer.data()), buffer.size());
    ::binary::Generator generator;
    ::binary::AddConverter<::binary::converters::StringConverter>(generator);
    ::binary::AddConverter<SimplePersonConverter>(generator);
    auto converter = ::binary::GetConverter<SimplePerson>(generator);
    auto result = converter->Decode(span);
    BOOST_REQUIRE_EQUAL(age, result.GetAge());
    BOOST_REQUIRE_EQUAL(name, result.GetName());
}

BOOST_AUTO_TEST_SUITE_END()
}
