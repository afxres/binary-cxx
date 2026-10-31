#include <boost/test/unit_test.hpp>

#include <binary/Allocator.hpp>
#include <binary/Generator.hpp>
#include <binary/GeneratorExtensions.hpp>
#include <binary/components/NamedObjectConverter.hpp>
#include <binary/converters/LittleEndianConverter.hpp>
#include <binary/converters/LittleEndianStringConverter.hpp>

#include <cstdint>
#include <string>

namespace tests::binary::components::NamedObjectTests {
BOOST_AUTO_TEST_SUITE(NamedObjectConverterTests)

struct OptionalModel {
    std::string Name;
    std::string Note;
    std::int32_t Count{};
};

struct OptionalSchema {
    static constexpr auto Members = std::tuple{
        ::binary::components::NamedMember{"Name", &OptionalModel::Name},
        ::binary::components::NamedMember{"Note", &OptionalModel::Note, true},
        ::binary::components::NamedMember{"Count", &OptionalModel::Count, true},
    };
};

using OptionalNamedObjectConverter = ::binary::components::NamedObjectConverter<OptionalModel, OptionalSchema>;

BOOST_AUTO_TEST_CASE(OptionalNamedObjectConverterMissingMemberTest) {
    ::binary::Generator generator;
    ::binary::AddConverter<::binary::converters::LittleEndianConverter<std::int32_t>>(generator);
    ::binary::AddConverter<::binary::converters::LittleEndianStringConverter<std::string>>(generator);
    ::binary::AddConverter<OptionalNamedObjectConverter>(generator);
    auto converter = ::binary::GetConverter<OptionalModel>(generator);
    auto buffer = ::binary::Allocator::Invoke([](auto& allocator) {
        ::binary::EncodeWithLengthPrefix(allocator, std::span<const std::byte>(reinterpret_cast<const std::byte*>("Name"), 4));
        ::binary::EncodeWithLengthPrefix(allocator, std::span<const std::byte>(reinterpret_cast<const std::byte*>("hello"), 5));
    });
    auto result = converter->Decode(buffer);
    BOOST_REQUIRE_EQUAL(std::string("hello"), result.Name);
    BOOST_REQUIRE(result.Note.empty());
    BOOST_REQUIRE_EQUAL(0, result.Count);
}

BOOST_AUTO_TEST_CASE(OptionalNamedObjectConverterRoundTripTest) {
    ::binary::Generator generator;
    ::binary::AddConverter<::binary::converters::LittleEndianConverter<std::int32_t>>(generator);
    ::binary::AddConverter<::binary::converters::LittleEndianStringConverter<std::string>>(generator);
    ::binary::AddConverter<OptionalNamedObjectConverter>(generator);
    auto converter = ::binary::GetConverter<OptionalModel>(generator);
    OptionalModel source;
    source.Name = "hello";
    source.Note = "note";
    source.Count = 7;
    auto buffer = ::binary::Allocator::Invoke([&converter, &source](auto& allocator) { converter->Encode(allocator, source); });
    auto result = converter->Decode(buffer);
    BOOST_REQUIRE_EQUAL(source.Name, result.Name);
    BOOST_REQUIRE_EQUAL(source.Note, result.Note);
    BOOST_REQUIRE_EQUAL(source.Count, result.Count);
}

BOOST_AUTO_TEST_SUITE_END()
}
