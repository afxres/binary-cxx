#include <boost/test/unit_test.hpp>

#include <binary/Allocator.hpp>
#include <binary/Generator.hpp>
#include <binary/GeneratorExtensions.hpp>
#include <binary/components/TupleObjectConverter.hpp>
#include <binary/converters/LittleEndianConverter.hpp>
#include <binary/converters/LittleEndianStringConverter.hpp>
#include <binary/experimental/Converter.hpp>
#include <binary/experimental/components/TupleObjectConverter.hpp>

#include <algorithm>
#include <cstdint>
#include <span>
#include <string>
#include <tuple>

namespace tests::binary::experimental::components::TupleObjectConverterTests {
struct Pair {
    std::int32_t X;
    std::int32_t Y;
    std::string Name;
};

struct PairSchema {
    static constexpr auto Members = std::tuple{
        ::binary::components::TupleMember{&Pair::X},
        ::binary::components::TupleMember{&Pair::Y},
        ::binary::components::TupleMember{&Pair::Name},
    };
};

PairSchema GetTupleObjectSchema(Pair*);

struct Ints {
    std::int32_t A;
    std::int32_t B;
};

struct IntsSchema {
    static constexpr auto Members = std::tuple{
        ::binary::components::TupleMember{&Ints::A},
        ::binary::components::TupleMember{&Ints::B},
    };
};

using PairVirtualConverter = ::binary::components::TupleObjectConverter<Pair, PairSchema>;
using PairTemplateConverter = ::binary::experimental::components::TupleObjectConverter<Pair, PairSchema>;
using IntsVirtualConverter = ::binary::components::TupleObjectConverter<Ints, IntsSchema>;
using IntsTemplateConverter = ::binary::experimental::components::TupleObjectConverter<Ints, IntsSchema>;

BOOST_AUTO_TEST_CASE(TupleObjectConverterWireCompatibilityTest) {
    ::binary::Generator generator;
    ::binary::AddConverter<::binary::converters::LittleEndianConverter<std::int32_t>>(generator);
    ::binary::AddConverter<::binary::converters::LittleEndianStringConverter<std::string>>(generator);
    PairVirtualConverter reference(generator);
    Pair source{42, 1024, "hello"};

    auto expected = ::binary::Allocator::Invoke([&](auto& allocator) { reference.Encode(allocator, source); });
    auto expectedAuto = ::binary::Allocator::Invoke([&](auto& allocator) { reference.EncodeAuto(allocator, source); });
    auto actual = ::binary::Allocator::Invoke([&](auto& allocator) { PairTemplateConverter::Encode(allocator, source); });
    auto actualAuto = ::binary::Allocator::Invoke([&](auto& allocator) { PairTemplateConverter::EncodeAuto(allocator, source); });
    BOOST_REQUIRE_EQUAL(expected.size(), actual.size());
    BOOST_REQUIRE(std::equal(expected.begin(), expected.end(), actual.begin()));
    BOOST_REQUIRE_EQUAL(expectedAuto.size(), actualAuto.size());
    BOOST_REQUIRE(std::equal(expectedAuto.begin(), expectedAuto.end(), actualAuto.begin()));

    auto result = PairTemplateConverter::Decode(std::span<const std::byte>(actual.data(), actual.size()));
    BOOST_REQUIRE_EQUAL(result.X, source.X);
    BOOST_REQUIRE_EQUAL(result.Y, source.Y);
    BOOST_REQUIRE_EQUAL(result.Name, source.Name);

    std::span<const std::byte> span(actualAuto.data(), actualAuto.size());
    auto autoResult = PairTemplateConverter::DecodeAuto(span);
    BOOST_REQUIRE_EQUAL(autoResult.X, source.X);
    BOOST_REQUIRE_EQUAL(autoResult.Y, source.Y);
    BOOST_REQUIRE_EQUAL(autoResult.Name, source.Name);
    BOOST_REQUIRE_EQUAL(span.size(), 0);
    BOOST_REQUIRE_EQUAL(PairTemplateConverter::Length(), reference.Length());
}

BOOST_AUTO_TEST_CASE(TupleObjectConverterAliasTest) {
    ::binary::Generator generator;
    ::binary::AddConverter<::binary::converters::LittleEndianConverter<std::int32_t>>(generator);
    ::binary::AddConverter<::binary::converters::LittleEndianStringConverter<std::string>>(generator);
    PairVirtualConverter reference(generator);
    Pair source{7, 9, ""};

    auto expected = ::binary::Allocator::Invoke([&](auto& allocator) { reference.Encode(allocator, source); });
    using HelperConverter = ::binary::experimental::Converter<Pair>;
    auto actual = ::binary::Allocator::Invoke([&](auto& allocator) { HelperConverter::Encode(allocator, source); });
    BOOST_REQUIRE_EQUAL(expected.size(), actual.size());
    BOOST_REQUIRE(std::equal(expected.begin(), expected.end(), actual.begin()));
}

BOOST_AUTO_TEST_CASE(TupleObjectConverterFixedLengthTest) {
    ::binary::Generator generator;
    ::binary::AddConverter<::binary::converters::LittleEndianConverter<std::int32_t>>(generator);
    IntsVirtualConverter reference(generator);
    BOOST_REQUIRE_EQUAL(IntsTemplateConverter::Length(), 8);
    BOOST_REQUIRE_EQUAL(IntsTemplateConverter::Length(), reference.Length());
    Ints source{3, 5};
    auto expected = ::binary::Allocator::Invoke([&](auto& allocator) { reference.Encode(allocator, source); });
    auto actual = ::binary::Allocator::Invoke([&](auto& allocator) { IntsTemplateConverter::Encode(allocator, source); });
    BOOST_REQUIRE(std::equal(expected.begin(), expected.end(), actual.begin()));
}

class Box {
private:
    std::int32_t a{};
    std::int32_t b{};

public:
    Box() = default;
    Box(std::int32_t a, std::int32_t b)
        : a(a)
        , b(b) {
    }

    std::int32_t GetA() const { return a; }
    void SetA(std::int32_t value) { a = value; }
    std::int32_t GetB() const { return b; }
    void SetB(std::int32_t value) { b = value; }
};

struct BoxSchema {
    static constexpr auto Members = std::tuple{
        ::binary::components::TupleMember{[](const Box& item) { return item.GetA(); }, [](Box& item, std::int32_t value) { item.SetA(value); }},
        ::binary::components::TupleMember{[](const Box& item) { return item.GetB(); }, [](Box& item, std::int32_t value) { item.SetB(value); }},
    };
};

BoxSchema GetTupleObjectSchema(Box*);

using BoxVirtualConverter = ::binary::components::TupleObjectConverter<Box, BoxSchema>;
using BoxTemplateConverter = ::binary::experimental::components::TupleObjectConverter<Box, BoxSchema>;

BOOST_AUTO_TEST_CASE(TupleObjectConverterCustomAccessorTest) {
    ::binary::Generator generator;
    ::binary::AddConverter<::binary::converters::LittleEndianConverter<std::int32_t>>(generator);
    BoxVirtualConverter reference(generator);
    Box source{11, 22};

    auto expected = ::binary::Allocator::Invoke([&](auto& allocator) { reference.Encode(allocator, source); });
    auto actual = ::binary::Allocator::Invoke([&](auto& allocator) { BoxTemplateConverter::Encode(allocator, source); });
    BOOST_REQUIRE_EQUAL(expected.size(), actual.size());
    BOOST_REQUIRE(std::equal(expected.begin(), expected.end(), actual.begin()));
    BOOST_REQUIRE_EQUAL(BoxTemplateConverter::Length(), reference.Length());

    auto result = BoxTemplateConverter::Decode(std::span<const std::byte>(actual.data(), actual.size()));
    BOOST_REQUIRE_EQUAL(result.GetA(), 11);
    BOOST_REQUIRE_EQUAL(result.GetB(), 22);

    using HelperConverter = ::binary::experimental::Converter<Box>;
    auto helper = ::binary::Allocator::Invoke([&](auto& allocator) { HelperConverter::Encode(allocator, source); });
    BOOST_REQUIRE(std::equal(expected.begin(), expected.end(), helper.begin()));
}
}
