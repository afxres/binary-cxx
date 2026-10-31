#include <boost/test/data/test_case.hpp>
#include <boost/test/unit_test.hpp>

#include <binary/Generator.hpp>
#include <binary/GeneratorExtensions.hpp>
#include <binary/Token.hpp>
#include <binary/components/NamedObjectConverter.hpp>
#include <binary/converters/LittleEndianConverter.hpp>
#include <binary/converters/LittleEndianStringConverter.hpp>

namespace tests::binary::TokenTests {
BOOST_AUTO_TEST_SUITE(TokenTests)

BOOST_AUTO_TEST_CASE(TokenWithDefaultValueTest) {
    ::binary::Generator generator;
    ::binary::AddConverter<::binary::converters::LittleEndianStringConverter<std::string>>(generator);
    auto token = ::binary::Token(generator, {});
    BOOST_REQUIRE(token.Children().empty());
    BOOST_REQUIRE(token.Span().empty());
}

std::vector<std::string> TokenWithInvalidBytesTestData = {
    {std::string("\x01", 1)},
    {std::string("\x00\x01", 2)},
};

BOOST_DATA_TEST_CASE(TokenWithInvalidBytesTest, TokenWithInvalidBytesTestData, source) {
    ::binary::Generator generator;
    ::binary::AddConverter<::binary::converters::LittleEndianStringConverter<std::string>>(generator);
    auto span = std::span(reinterpret_cast<const std::byte*>(source.data()), source.size());
    auto token = ::binary::Token(generator, span);
    BOOST_REQUIRE(token.Children().empty());
    BOOST_REQUIRE(token.Span().data() == span.data() && token.Span().size() == span.size());
    auto nestedHandler = [](const std::length_error& e) {
        BOOST_REQUIRE_EQUAL(e.what(), "not enough bytes or byte sequence invalid");
        return true;
    };
    BOOST_REQUIRE_EXCEPTION(
        (void)token.At(""),
        std::invalid_argument,
        [nestedHandler](const std::invalid_argument& e) {
            BOOST_REQUIRE_EQUAL(e.what(), "key '' not found");
            BOOST_REQUIRE_EXCEPTION(
                std::rethrow_if_nested(e),
                std::length_error,
                nestedHandler
            );
            return true;
        }
    );
    BOOST_REQUIRE_EXCEPTION(
        (void)token.At("fake"),
        std::invalid_argument,
        [nestedHandler](const std::invalid_argument& e) {
            BOOST_REQUIRE_EQUAL(e.what(), "key 'fake' not found");
            BOOST_REQUIRE_EXCEPTION(
                std::rethrow_if_nested(e),
                std::length_error,
                nestedHandler
            );
            return true;
        }
    );
}

struct Item {
    int32_t id;
    std::string name;
    bool operator==(const Item&) const = default;
};

struct Case {
    std::string path;
    Item main;
    Item backup;
    bool operator==(const Case&) const = default;
};

struct ItemSchema {
    static constexpr auto Members = std::tuple{
        ::binary::components::NamedMember{"id", &Item::id},
        ::binary::components::NamedMember{"name", &Item::name},
    };
};

using ItemConverter = ::binary::components::NamedObjectConverter<Item, ItemSchema>;

struct CaseSchema {
    static constexpr auto Members = std::tuple{
        ::binary::components::NamedMember{"path", &Case::path},
        ::binary::components::NamedMember{"main", &Case::main},
        ::binary::components::NamedMember{"backup", &Case::backup},
    };
};

using CaseConverter = ::binary::components::NamedObjectConverter<Case, CaseSchema>;

BOOST_AUTO_TEST_CASE(TokenWithSimpleNamedObjectTest) {
    ::binary::Generator generator;
    ::binary::AddConverter<::binary::converters::LittleEndianConverter<int32_t>>(generator);
    ::binary::AddConverter<::binary::converters::LittleEndianStringConverter<std::string>>(generator);
    ::binary::AddConverter<ItemConverter>(generator);
    ::binary::AddConverter<CaseConverter>(generator);
    auto converter = ::binary::GetConverter<Case>(generator);
    Case source = {
        .path = "some case",
        .main = {
            .id = 384,
            .name = "first",
        },
        .backup = {
            .id = 1024,
            .name = "second",
        },
    };
    auto buffer = ::binary::Allocator::Invoke([&](auto& allocator) { return converter->Encode(allocator, source); });
    auto token = ::binary::Token(generator, buffer);

    auto path = token.At("path");
    auto main = token.At("main");
    auto backup = token.At("backup");
    BOOST_REQUIRE_EQUAL(3, token.Children().size());

    auto firstId = main.At("id");
    auto firstName = main.At("name");
    BOOST_REQUIRE_EQUAL(2, main.Children().size());

    auto secondId = backup.At("id");
    auto secondName = backup.At("name");
    BOOST_REQUIRE_EQUAL(2, backup.Children().size());

    Case actual;
    actual.path = path.As<std::string>();
    actual.main.id = firstId.As<int32_t>();
    actual.main.name = firstName.As<std::string>();
    actual.backup.id = secondId.As<int32_t>();
    actual.backup.name = secondName.As<std::string>();
    BOOST_REQUIRE(source == actual);

    for (auto& i : std::initializer_list{path, firstId, firstName, secondId, secondName}) {
        BOOST_REQUIRE_EQUAL(0, i.Children().size());
    }

    BOOST_REQUIRE_EXCEPTION(
        (void)token.At("invalid"),
        std::invalid_argument,
        [](const std::invalid_argument& e) {
            BOOST_REQUIRE_EQUAL(e.what(), "key 'invalid' not found");
            std::rethrow_if_nested(e);
            return true;
        }
    );
}

BOOST_AUTO_TEST_CASE(TokenWithDuplicateKeyTest) {
    ::binary::Generator generator;
    ::binary::AddConverter<::binary::converters::LittleEndianStringConverter<std::string>>(generator);
    auto buffer = ::binary::Allocator::Invoke([](auto& allocator) {
        ::binary::EncodeWithLengthPrefix(allocator, std::span<const std::byte>(reinterpret_cast<const std::byte*>("id"), 2));
        ::binary::EncodeWithLengthPrefix(allocator, std::span<const std::byte>(reinterpret_cast<const std::byte*>("first"), 5));
        ::binary::EncodeWithLengthPrefix(allocator, std::span<const std::byte>(reinterpret_cast<const std::byte*>("id"), 2));
        ::binary::EncodeWithLengthPrefix(allocator, std::span<const std::byte>(reinterpret_cast<const std::byte*>("second"), 6));
    });
    auto token = ::binary::Token(generator, buffer);
    BOOST_REQUIRE_EQUAL(1, token.Children().size());
    BOOST_REQUIRE_EQUAL(std::string("first"), token.At("id").As<std::string>());
}

BOOST_AUTO_TEST_SUITE_END()
}
