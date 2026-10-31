#include <boost/test/unit_test.hpp>

#include <binary/Allocator.hpp>
#include <binary/Generator.hpp>
#include <binary/GeneratorExtensions.hpp>
#include <binary/components/MemberDescriptor.hpp>
#include <binary/components/NamedObjectConverter.hpp>
#include <binary/converters/LittleEndianStringConverter.hpp>

#include <algorithm>
#include <cstdint>
#include <string>

namespace tests::binary::components::NamedObjectTests {
BOOST_AUTO_TEST_SUITE(PolicyNamedObjectConverterTests)

class TextInt32Converter : public ::binary::Converter<std::int32_t> {
private:
    ::binary::converters::LittleEndianStringConverter<std::string> converter;

public:
    explicit TextInt32Converter()
        : ::binary::Converter<std::int32_t>(0) {}

    void Encode(::binary::Allocator& allocator, const std::int32_t& item) override {
        this->converter.Encode(allocator, std::to_string(item));
    }

    std::int32_t Decode(std::span<const std::byte> span) override {
        return std::stoi(this->converter.Decode(span));
    }
};

struct PolicyModel {
    std::int32_t Age{};
    std::string Name;
};

struct PolicySchema {
    static constexpr auto Members = std::tuple{
        ::binary::components::NamedMember{
            "Age",
            [](const PolicyModel& item) { return item.Age; },
            [](PolicyModel& item, auto&& value) { item.Age = value; },
            ::binary::components::FixedConverterPolicy<TextInt32Converter>{},
        },
        ::binary::components::NamedMember{"Name", &PolicyModel::Name},
    };
};

using PolicyNamedObjectConverter = ::binary::components::NamedObjectConverter<PolicyModel, PolicySchema>;

BOOST_AUTO_TEST_CASE(PolicyNamedObjectConverterEncodeDecodeTest) {
    ::binary::Generator generator;
    ::binary::AddConverter<::binary::converters::LittleEndianStringConverter<std::string>>(generator);
    ::binary::AddConverter<PolicyNamedObjectConverter>(generator);
    auto converter = ::binary::GetConverter<PolicyModel>(generator);
    PolicyModel source;
    source.Age = 18;
    source.Name = "Alice";
    auto buffer = ::binary::Allocator::Invoke([&converter, &source](auto& allocator) { converter->Encode(allocator, source); });
    auto expected = ::binary::Allocator::Invoke([](auto& allocator) {
        ::binary::EncodeWithLengthPrefix(allocator, std::span<const std::byte>(reinterpret_cast<const std::byte*>("Age"), 3));
        ::binary::EncodeWithLengthPrefix(allocator, std::span<const std::byte>(reinterpret_cast<const std::byte*>("18"), 2));
        ::binary::EncodeWithLengthPrefix(allocator, std::span<const std::byte>(reinterpret_cast<const std::byte*>("Name"), 4));
        ::binary::EncodeWithLengthPrefix(allocator, std::span<const std::byte>(reinterpret_cast<const std::byte*>("Alice"), 5));
    });
    BOOST_REQUIRE_EQUAL(expected.size(), buffer.size());
    BOOST_REQUIRE(std::equal(expected.begin(), expected.end(), buffer.begin()));
    auto result = converter->Decode(buffer);
    BOOST_REQUIRE_EQUAL(source.Age, result.Age);
    BOOST_REQUIRE_EQUAL(source.Name, result.Name);
}

BOOST_AUTO_TEST_SUITE_END()
}
