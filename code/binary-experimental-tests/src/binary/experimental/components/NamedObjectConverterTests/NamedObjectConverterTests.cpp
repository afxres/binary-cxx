#include <boost/test/unit_test.hpp>

#include <binary/Allocator.hpp>
#include <binary/Generator.hpp>
#include <binary/GeneratorExtensions.hpp>
#include <binary/components/NamedObjectConverter.hpp>
#include <binary/converters/LittleEndianConverter.hpp>
#include <binary/converters/LittleEndianStringConverter.hpp>
#include <binary/experimental/Converter.hpp>

#include <algorithm>
#include <cstdint>
#include <span>
#include <string>
#include <string_view>
#include <tuple>

namespace tests::binary::experimental::components::NamedObjectConverterTests {
struct Model {
    std::int32_t Id;
    std::string Name;
};

struct Schema {
    static constexpr auto Members = std::tuple{
        ::binary::components::NamedMember{"Id", &Model::Id},
        ::binary::components::NamedMember{"Name", &Model::Name},
    };
};

Schema GetNamedObjectSchema(Model*);

struct OptionalModel {
    std::string Name;
    std::string Note;
    std::int32_t Count;
};

struct OptionalSchema {
    static constexpr auto Members = std::tuple{
        ::binary::components::NamedMember{"Name", &OptionalModel::Name},
        ::binary::components::NamedMember{"Note", &OptionalModel::Note, true},
        ::binary::components::NamedMember{"Count", &OptionalModel::Count, true},
    };
};

OptionalSchema GetNamedObjectSchema(OptionalModel*);
}

namespace tests::binary::experimental::components::NamedObjectConverterTests {
BOOST_AUTO_TEST_SUITE(NamedObjectConverterTests)

BOOST_AUTO_TEST_CASE(NamedObjectConverterWireCompatibilityTest) {
    ::binary::Generator generator;
    ::binary::AddConverter<::binary::converters::LittleEndianConverter<std::int32_t>>(generator);
    ::binary::AddConverter<::binary::converters::LittleEndianStringConverter<std::string>>(generator);
    auto reference = std::make_shared<::binary::components::NamedObjectConverter<Model, Schema>>(generator);
    Model source{1024, "hello"};
    auto expected = ::binary::Allocator::Invoke([&](auto& allocator) { reference->Encode(allocator, source); });

    using DirectConverter = ::binary::experimental::components::NamedObjectConverter<Model, Schema>;
    auto direct = ::binary::Allocator::Invoke([&](auto& allocator) { DirectConverter::Encode(allocator, source); });
    BOOST_REQUIRE_EQUAL(expected.size(), direct.size());
    BOOST_REQUIRE(std::equal(expected.begin(), expected.end(), direct.begin()));

    using HelperConverter = ::binary::experimental::Converter<Model>;
    auto helper = ::binary::Allocator::Invoke([&](auto& allocator) { HelperConverter::Encode(allocator, source); });
    BOOST_REQUIRE_EQUAL(expected.size(), helper.size());
    BOOST_REQUIRE(std::equal(expected.begin(), expected.end(), helper.begin()));

    std::span<const std::byte> span(direct);
    auto result = DirectConverter::Decode(span);
    BOOST_REQUIRE_EQUAL(source.Id, result.Id);
    BOOST_REQUIRE_EQUAL(source.Name, result.Name);
}

BOOST_AUTO_TEST_CASE(NamedObjectConverterMissingKeyTest) {
    using ConverterType = ::binary::experimental::components::NamedObjectConverter<Model, Schema>;
    auto buffer = ::binary::Allocator::Invoke([](auto& allocator) {
        ::binary::EncodeWithLengthPrefix(allocator, std::span<const std::byte>(reinterpret_cast<const std::byte*>("Id"), 2));
        ::binary::EncodeWithLengthPrefix(allocator, std::span<const std::byte>(reinterpret_cast<const std::byte*>("abcd"), 4));
    });

    std::span<const std::byte> span(buffer);
    BOOST_REQUIRE_EXCEPTION(
        ConverterType::Decode(span),
        std::invalid_argument,
        [](const std::invalid_argument& e) {
            BOOST_REQUIRE_EQUAL(std::string_view(e.what()), std::string_view("named key 'Name' does not exist"));
            return true;
        }
    );
}

BOOST_AUTO_TEST_CASE(NamedObjectConverterOptionalMemberTest) {
    using ConverterType = ::binary::experimental::components::NamedObjectConverter<OptionalModel, OptionalSchema>;
    auto buffer = ::binary::Allocator::Invoke([](auto& allocator) {
        ::binary::EncodeWithLengthPrefix(allocator, std::span<const std::byte>(reinterpret_cast<const std::byte*>("Name"), 4));
        ::binary::EncodeWithLengthPrefix(allocator, std::span<const std::byte>(reinterpret_cast<const std::byte*>("hello"), 5));
    });

    std::span<const std::byte> span(buffer);
    const auto result = ConverterType::Decode(span);
    BOOST_REQUIRE_EQUAL(result.Name, "hello");
    BOOST_REQUIRE_EQUAL(result.Note, "");
    BOOST_REQUIRE_EQUAL(result.Count, 0);
}

BOOST_AUTO_TEST_SUITE_END()
}
