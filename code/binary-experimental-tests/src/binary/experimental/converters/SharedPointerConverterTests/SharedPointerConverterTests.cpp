#include <boost/test/unit_test.hpp>

#include <binary/Allocator.hpp>

#include <binary/experimental/Converter.hpp>
#include <binary/experimental/converters/LittleEndianConverter.hpp>
#include <binary/experimental/converters/LittleEndianStringConverter.hpp>
#include <binary/experimental/converters/SharedPointerConverter.hpp>

#include <cstdint>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

namespace tests::binary::experimental::converters::SharedPointerConverterTests {
BOOST_AUTO_TEST_SUITE(SharedPointerConverterTests)

namespace {
std::string ToHex(std::span<const std::byte> span) {
    static constexpr std::string_view Digits = "0123456789abcdef";
    std::string result;
    result.reserve(span.size() * 2);
    for (std::byte i : span) {
        auto value = static_cast<size_t>(i);
        result.push_back(Digits[value / 16]);
        result.push_back(Digits[value % 16]);
    }
    return result;
}

template <typename T>
std::string EncodeHex(const T& item) {
    auto buffer = ::binary::Allocator::Invoke([&item](auto& allocator) { ::binary::experimental::Converter<T>::Encode(allocator, item); });
    return ToHex(buffer);
}

template <typename T>
std::string EncodeAutoHex(const T& item) {
    using C = ::binary::experimental::Converter<T>;
    auto buffer = ::binary::Allocator::Invoke([&item](auto& allocator) { C::EncodeAuto(allocator, item); });
    return ToHex(buffer);
}

template <typename T>
std::vector<std::byte> EncodeAutoBuffer(const T& item) {
    using C = ::binary::experimental::Converter<T>;
    return ::binary::Allocator::Invoke([&item](auto& allocator) { C::EncodeAuto(allocator, item); });
}
}

BOOST_AUTO_TEST_CASE(SharedPointerConverterLengthTest) {
    BOOST_REQUIRE_EQUAL(4, ::binary::experimental::Converter<std::shared_ptr<std::int32_t>>::Length());
    BOOST_REQUIRE_EQUAL(0, ::binary::experimental::Converter<std::shared_ptr<std::string>>::Length());
}

BOOST_AUTO_TEST_CASE(SharedPointerConverterWireTest) {
    BOOST_REQUIRE_EQUAL("05000000", EncodeHex(std::make_shared<std::int32_t>(5)));
    BOOST_REQUIRE_EQUAL("05000000", EncodeAutoHex(std::make_shared<std::int32_t>(5)));

    BOOST_REQUIRE_EQUAL("616263", EncodeHex(std::make_shared<std::string>("abc")));
    BOOST_REQUIRE_EQUAL("03616263", EncodeAutoHex(std::make_shared<std::string>("abc")));
}

BOOST_AUTO_TEST_CASE(SharedPointerConverterRoundTripTest) {
    using T = std::shared_ptr<std::string>;

    auto bytes = EncodeAutoBuffer(std::make_shared<std::string>("abc"));
    std::span<const std::byte> span(bytes);
    auto first = ::binary::experimental::Converter<T>::DecodeAuto(span);
    BOOST_REQUIRE_EQUAL(0, span.size());
    BOOST_REQUIRE(first != nullptr);
    BOOST_REQUIRE_EQUAL("abc", *first);

    std::span<const std::byte> again(bytes);
    auto second = ::binary::experimental::Converter<T>::DecodeAuto(again);
    BOOST_REQUIRE(first != second);
    *second = "xyz";
    BOOST_REQUIRE_EQUAL("abc", *first);
}

BOOST_AUTO_TEST_CASE(SharedPointerConverterNullTest) {
    BOOST_REQUIRE_EXCEPTION(
        EncodeHex(std::shared_ptr<std::int32_t>()),
        std::invalid_argument,
        [](const std::invalid_argument& e) { return std::string(e.what()).starts_with("null pointer"); }
    );
}

BOOST_AUTO_TEST_SUITE_END()
}
