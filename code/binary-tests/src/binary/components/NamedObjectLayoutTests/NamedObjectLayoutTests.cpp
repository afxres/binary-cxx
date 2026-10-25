#include <boost/test/unit_test.hpp>

#include <binary/Allocator.hpp>
#include <binary/ConverterExtensions.hpp>
#include <binary/components/MemberDescriptor.hpp>
#include <binary/components/NamedObjectLayout.hpp>

#include <array>
#include <cstddef>
#include <cstdint>
#include <span>
#include <stdexcept>
#include <string>
#include <string_view>
#include <tuple>

namespace tests::binary::components::NamedObjectLayoutTests {
BOOST_AUTO_TEST_SUITE(NamedObjectLayoutTests)

struct SmallModel {
    std::int32_t Id;
    std::string Name;
    std::int32_t Count;
};

struct SmallSchema {
    static constexpr auto Members = std::tuple{
        ::binary::components::NamedMember{"Id", &SmallModel::Id},
        ::binary::components::NamedMember{"Name", &SmallModel::Name, true},
        ::binary::components::NamedMember{"Count", &SmallModel::Count},
    };
};

using SmallLayout = ::binary::components::NamedObjectLayout<SmallSchema>;

std::span<const std::byte> AsBytes(std::string_view text) {
    return std::span<const std::byte>(reinterpret_cast<const std::byte*>(text.data()), text.size());
}

void EncodeMember(::binary::Allocator& allocator, std::string_view name, std::span<const std::byte> value) {
    ::binary::EncodeWithLengthPrefix(allocator, AsBytes(name));
    ::binary::EncodeWithLengthPrefix(allocator, value);
}

BOOST_AUTO_TEST_CASE(NamedObjectLayoutFindTest) {
    BOOST_REQUIRE_EQUAL(SmallLayout::Query("Id"), 0);
    BOOST_REQUIRE_EQUAL(SmallLayout::Query("Name"), 1);
    BOOST_REQUIRE_EQUAL(SmallLayout::Query("Count"), 2);
    BOOST_REQUIRE_EQUAL(SmallLayout::Query("Missing"), SIZE_MAX);
    BOOST_REQUIRE_EQUAL(SmallLayout::Query("a very long unknown key"), SIZE_MAX);
}

BOOST_AUTO_TEST_CASE(NamedObjectLayoutParseTest) {
    const std::array<std::byte, 4> one{std::byte{1}, std::byte{0}, std::byte{0}, std::byte{0}};
    const std::array<std::byte, 4> two{std::byte{2}, std::byte{0}, std::byte{0}, std::byte{0}};
    auto buffer = ::binary::Allocator::Invoke([&](auto& allocator) {
        EncodeMember(allocator, "Count", two);
        EncodeMember(allocator, "Unknown", AsBytes("x"));
        EncodeMember(allocator, "Id", one);
    });

    std::array<std::span<const std::byte>, SmallLayout::Count> slices{};
    SmallLayout::Parse(std::span<const std::byte>(buffer.data(), buffer.size()), slices);
    BOOST_REQUIRE(slices[0].data() != nullptr);
    BOOST_REQUIRE_EQUAL(slices[0].size(), 4);
    BOOST_REQUIRE_EQUAL(std::to_integer<int>(slices[0][0]), 1);
    BOOST_REQUIRE(slices[1].data() == nullptr);
    BOOST_REQUIRE(slices[2].data() != nullptr);
    BOOST_REQUIRE_EQUAL(std::to_integer<int>(slices[2][0]), 2);
}

BOOST_AUTO_TEST_CASE(NamedObjectLayoutDuplicateTest) {
    const std::array<std::byte, 4> one{std::byte{1}, std::byte{0}, std::byte{0}, std::byte{0}};
    auto buffer = ::binary::Allocator::Invoke([&](auto& allocator) {
        EncodeMember(allocator, "Id", one);
        EncodeMember(allocator, "Id", one);
    });

    std::array<std::span<const std::byte>, SmallLayout::Count> slices{};
    BOOST_REQUIRE_EXCEPTION(
        SmallLayout::Parse(std::span<const std::byte>(buffer.data(), buffer.size()), slices),
        std::invalid_argument,
        [](const std::invalid_argument& exception) {
            BOOST_REQUIRE_EQUAL(std::string_view(exception.what()), std::string_view("named key 'Id' already exists"));
            return true;
        }
    );
}

BOOST_AUTO_TEST_CASE(NamedObjectLayoutMissingTest) {
    const std::array<std::byte, 4> one{std::byte{1}, std::byte{0}, std::byte{0}, std::byte{0}};
    auto buffer = ::binary::Allocator::Invoke([&](auto& allocator) {
        EncodeMember(allocator, "Id", one);
    });

    std::array<std::span<const std::byte>, SmallLayout::Count> slices{};
    BOOST_REQUIRE_EXCEPTION(
        SmallLayout::Parse(std::span<const std::byte>(buffer.data(), buffer.size()), slices),
        std::invalid_argument,
        [](const std::invalid_argument& exception) {
            BOOST_REQUIRE_EQUAL(std::string_view(exception.what()), std::string_view("named key 'Count' does not exist"));
            return true;
        }
    );
}

struct LargeModel {
    std::int32_t A;
    std::int32_t B;
    std::int32_t C;
    std::int32_t D;
    std::int32_t E;
    std::int32_t F;
    std::int32_t G;
    std::int32_t H;
    std::int32_t I;
    std::int32_t J;
    std::int32_t K;
    std::int32_t L;
};

struct LargeSchema {
    static constexpr auto Members = std::tuple{
        ::binary::components::NamedMember{"member_value_0000", &LargeModel::A},
        ::binary::components::NamedMember{"member_value_0001", &LargeModel::B},
        ::binary::components::NamedMember{"member_value_0002", &LargeModel::C},
        ::binary::components::NamedMember{"member_value_0003", &LargeModel::D},
        ::binary::components::NamedMember{"member_value_0004", &LargeModel::E},
        ::binary::components::NamedMember{"member_value_0005", &LargeModel::F},
        ::binary::components::NamedMember{"member_value_0006", &LargeModel::G},
        ::binary::components::NamedMember{"member_value_0007", &LargeModel::H},
        ::binary::components::NamedMember{"member_value_0008", &LargeModel::I},
        ::binary::components::NamedMember{"member_value_0009", &LargeModel::J},
        ::binary::components::NamedMember{"member_value_0010", &LargeModel::K},
        ::binary::components::NamedMember{"member_value_0011", &LargeModel::L},
    };
};

using LargeLayout = ::binary::components::NamedObjectLayout<LargeSchema>;

BOOST_AUTO_TEST_CASE(NamedObjectLayoutLargeTableTest) {
    BOOST_REQUIRE_EQUAL(LargeLayout::Count, 12);
    BOOST_REQUIRE_EQUAL(LargeLayout::Query("member_value_0000"), 0);
    BOOST_REQUIRE_EQUAL(LargeLayout::Query("member_value_0007"), 7);
    BOOST_REQUIRE_EQUAL(LargeLayout::Query("member_value_0011"), 11);
    BOOST_REQUIRE_EQUAL(LargeLayout::Query("member_value_0012"), SIZE_MAX);
    BOOST_REQUIRE_EQUAL(LargeLayout::Query("member"), SIZE_MAX);
}

BOOST_AUTO_TEST_CASE(NamedObjectLayoutDuplicateIndexTest) {
    constexpr std::array<std::string_view, 2> duplicate{"Age", "Age"};
    BOOST_REQUIRE_EQUAL(::binary::components::detail::GetDuplicateIndex(duplicate), 0);
    constexpr std::array<std::string_view, 3> unique{"Age", "Name", "Count"};
    BOOST_REQUIRE_EQUAL(::binary::components::detail::GetDuplicateIndex(unique), SIZE_MAX);
}

BOOST_AUTO_TEST_SUITE_END()
}
