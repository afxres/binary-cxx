#include <boost/test/data/test_case.hpp>
#include <boost/test/unit_test.hpp>

#include <binary/Generator.hpp>
#include <binary/GeneratorExtensions.hpp>
#include <binary/components/NamedObject.hpp>
#include <binary/converters/LittleEndianConverter.hpp>
#include <binary/converters/LittleEndianStringConverter.hpp>

namespace tests::binary::components::NamedObjectTests {
BOOST_AUTO_TEST_SUITE(SimplePersonNamedObjectConverterTests)

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

BINARY_NAMED_OBJECT_CONVERTER(SimplePerson, SimplePersonNamedObjectConverter)
BINARY_NAMED_MEMBER(Age)
BINARY_NAMED_MEMBER(Name)
BINARY_NAMED_OBJECT_CONVERTER_END()

BINARY_NAMED_OBJECT_CONVERTER(SimplePersonCustom, SimplePersonCustomNamedObjectConverter)
BINARY_NAMED_MEMBER_CUSTOM("Age", true, item.GetAge(), item.SetAge(result), std::make_shared<::binary::converters::LittleEndianConverter<int8_t>>())
BINARY_NAMED_MEMBER_CUSTOM("Name", true, item.GetName(), item.SetName(result), std::make_shared<::binary::converters::LittleEndianStringConverter<std::string>>())
BINARY_NAMED_OBJECT_CONVERTER_END()

BOOST_AUTO_TEST_CASE(SimplePersonNamedObjectConverterLengthTest) {
    ::binary::Generator generator;
    ::binary::AddConverter<::binary::converters::LittleEndianConverter<int8_t>>(generator);
    ::binary::AddConverter<::binary::converters::LittleEndianStringConverter<std::string>>(generator);
    ::binary::AddConverter<SimplePersonNamedObjectConverter>(generator);
    ::binary::AddConverter<SimplePersonCustomNamedObjectConverter>(generator);
    auto a = ::binary::GetConverter<SimplePerson>(generator);
    auto b = ::binary::GetConverter<SimplePersonCustom>(generator);
    BOOST_REQUIRE_EQUAL(typeid(SimplePersonNamedObjectConverter).name(), typeid(*a).name());
    BOOST_REQUIRE_EQUAL(typeid(SimplePersonCustomNamedObjectConverter).name(), typeid(*b).name());
    BOOST_REQUIRE_EQUAL(0, a->Length());
    BOOST_REQUIRE_EQUAL(0, b->Length());
}

std::vector<std::tuple<int8_t, std::string, int32_t>> SimplePersonTestData = {
    {18, "Alice", 17},
    {20, "Bob", 15},
};

BOOST_DATA_TEST_CASE(SimplePersonConverterEncodeDecodeTest, SimplePersonTestData, age, name, outputLength) {
    ::binary::Generator generator;
    ::binary::AddConverter<::binary::converters::LittleEndianConverter<int8_t>>(generator);
    ::binary::AddConverter<::binary::converters::LittleEndianStringConverter<std::string>>(generator);
    ::binary::AddConverter<SimplePersonNamedObjectConverter>(generator);
    ::binary::AddConverter<SimplePersonCustomNamedObjectConverter>(generator);
    auto a = ::binary::GetConverter<SimplePerson>(generator);
    auto b = ::binary::GetConverter<SimplePersonCustom>(generator);
    SimplePerson x;
    x.Age = age;
    x.Name = name;
    SimplePersonCustom y;
    y.SetAge(age);
    y.SetName(name);
    auto f = ::binary::Allocator::Invoke([&](auto& allocator) { a->Encode(allocator, x); });
    auto g = ::binary::Allocator::Invoke([&](auto& allocator) { b->Encode(allocator, y); });
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

std::vector<std::tuple<std::string, std::string>> SimplePersonDecodeKeyNotFoundTestData = {
    {std::string() + "\x03" + "Age\x01\x10", "Name"},
    {std::string() + "\x04" + "Name\x05" + "Alice", "Age"},
};

BOOST_DATA_TEST_CASE(SimplePersonDecodeKeyNotFoundTest, SimplePersonDecodeKeyNotFoundTestData, buffer, key) {
    std::span<const std::byte> span(reinterpret_cast<const std::byte*>(buffer.data()), buffer.size());
    std::string output = "named key '" + key + "' does not exist";
    ::binary::Generator generator;
    ::binary::AddConverter<::binary::converters::LittleEndianConverter<int8_t>>(generator);
    ::binary::AddConverter<::binary::converters::LittleEndianStringConverter<std::string>>(generator);
    ::binary::AddConverter<SimplePersonNamedObjectConverter>(generator);
    auto converter = ::binary::GetConverter<SimplePerson>(generator);
    BOOST_REQUIRE_EXCEPTION(
        converter->Decode(span),
        std::invalid_argument,
        [output](const std::invalid_argument& e) {
            BOOST_REQUIRE_EQUAL(e.what(), output);
            return true;
        });
}

std::vector<std::tuple<std::string, int8_t, std::string>> SimplePersonDecodeOptionalMemberTestData = {
    {"", 0, ""},
    {std::string() + "\x03" + "Age\x01\x12", 18, ""},
    {std::string() + "\x04" + "Name\x05" + "Alice", 0, "Alice"},
};

BOOST_DATA_TEST_CASE(SimplePersonDecodeOptionalMemberTest, SimplePersonDecodeOptionalMemberTestData, buffer, age, name) {
    std::span<const std::byte> span(reinterpret_cast<const std::byte*>(buffer.data()), buffer.size());
    ::binary::Generator generator;
    ::binary::AddConverter<::binary::converters::LittleEndianStringConverter<std::string>>(generator);
    ::binary::AddConverter<SimplePersonCustomNamedObjectConverter>(generator);
    auto converter = ::binary::GetConverter<SimplePersonCustom>(generator);
    auto result = converter->Decode(span);
    BOOST_REQUIRE_EQUAL(age, result.GetAge());
    BOOST_REQUIRE_EQUAL(name, result.GetName());
}

BINARY_NAMED_OBJECT_CONVERTER(SimplePerson, SimplePersonDuplicateKeyNamedObjectConverter)
BINARY_NAMED_MEMBER(Age)
BINARY_NAMED_MEMBER(Age)
BINARY_NAMED_OBJECT_CONVERTER_END()

BOOST_AUTO_TEST_CASE(SimplePersonDuplicateKeyNamedObjectConverterTest) {
    ::binary::Generator generator;
    ::binary::AddConverter<::binary::converters::LittleEndianConverter<int8_t>>(generator);
    ::binary::AddConverter<::binary::converters::LittleEndianStringConverter<std::string>>(generator);
    BOOST_REQUIRE_EXCEPTION(
        ::binary::AddConverter<SimplePersonDuplicateKeyNamedObjectConverter>(generator),
        std::invalid_argument,
        [](const std::invalid_argument& e) {
            BOOST_REQUIRE_EQUAL(e.what(), "named key 'Age' already exists");
            return true;
        });
}

class BadStringConverter : public ::binary::Converter<std::string> {
public:
    virtual void Encode([[maybe_unused]] ::binary::Allocator& allocator, [[maybe_unused]] const std::string& item) override {}
    virtual std::string Decode([[maybe_unused]] const std::span<const std::byte>& span) override { throw std::exception(); }
};

BOOST_AUTO_TEST_CASE(SimplePersonConverterWithBadStringConverterDuplicateKeyTest) {
    ::binary::Generator generator;
    ::binary::AddConverter<::binary::converters::LittleEndianConverter<int8_t>>(generator);
    ::binary::AddConverter<BadStringConverter>(generator);
    BOOST_REQUIRE_EXCEPTION(
        ::binary::AddConverter<SimplePersonNamedObjectConverter>(generator),
        std::invalid_argument,
        [](const std::invalid_argument& e) {
            BOOST_REQUIRE_EQUAL(e.what(), "named key 'Name' already exists");
            return true;
        });
}

std::vector<std::tuple<std::string, std::string>> SimplePersonConverterDecodeWithDuplicateKeyTestData = {
    {std::string() + "\x03" + "Age\x01\x14\x03" + "Age\x01\x14", "Age"},
    {std::string() + "\x04" + "Name\03" + "Bob\x04" + "Name\01" + "X", "Name"},
};

BOOST_DATA_TEST_CASE(SimplePersonConverterDecodeWithDuplicateKeyTest, SimplePersonConverterDecodeWithDuplicateKeyTestData, buffer, key) {
    std::span<const std::byte> span(reinterpret_cast<const std::byte*>(buffer.data()), buffer.size());
    std::string output = "named key '" + key + "' already exists";
    ::binary::Generator generator;
    ::binary::AddConverter<::binary::converters::LittleEndianConverter<int8_t>>(generator);
    ::binary::AddConverter<::binary::converters::LittleEndianStringConverter<std::string>>(generator);
    ::binary::AddConverter<SimplePersonNamedObjectConverter>(generator);
    auto converter = ::binary::GetConverter<SimplePerson>(generator);
    BOOST_REQUIRE_EXCEPTION(
        converter->Decode(span),
        std::invalid_argument,
        [output](const std::invalid_argument& e) {
            BOOST_REQUIRE_EQUAL(e.what(), output);
            return true;
        });
}

std::vector<std::tuple<std::string, uint8_t, std::string>> SimplePersonConverterDecodeWithUnknownKeyTestData = {
    {std::string() + "\x03" + "Age\x01\x16\x02" + "Id\x01\x20\x04" + "Name\x05" + "Alice", 22, "Alice"},
    {std::string() + "\x01" + "X\x01\xFF\x04" + "Name\x03" + "Tom\x03" + "Age\x01\x20\x04" + "Fake\x01\x80", 32, "Tom"}};

BOOST_DATA_TEST_CASE(SimplePersonConverterDecodeWithUnknownKeyTest, SimplePersonConverterDecodeWithUnknownKeyTestData, buffer, age, name) {
    std::span<const std::byte> span(reinterpret_cast<const std::byte*>(buffer.data()), buffer.size());
    ::binary::Generator generator;
    ::binary::AddConverter<::binary::converters::LittleEndianConverter<int8_t>>(generator);
    ::binary::AddConverter<::binary::converters::LittleEndianStringConverter<std::string>>(generator);
    ::binary::AddConverter<SimplePersonNamedObjectConverter>(generator);
    auto converter = ::binary::GetConverter<SimplePerson>(generator);
    auto result = converter->Decode(span);
    BOOST_REQUIRE_EQUAL(result.Age, age);
    BOOST_REQUIRE_EQUAL(result.Name, name);
}

BOOST_AUTO_TEST_SUITE_END()
}
