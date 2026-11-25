#include <boost/test/unit_test.hpp>

#include <binary/Allocator.hpp>

#include <binary/experimental/Converter.hpp>
#include <binary/experimental/converters/SmartPointerConverter.hpp>
#include <binary/experimental/helpers/ConverterDecodeAutoMethodHelper.hpp>
#include <binary/experimental/helpers/ConverterEncodeAutoMethodHelper.hpp>
#include <binary/experimental/helpers/ConverterEncodeWithLengthPrefixMethodHelper.hpp>

#include <cstdint>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

namespace tests::binary::experimental::converters::SmartPointerConverterTests {
BOOST_AUTO_TEST_SUITE(SmartPointerConverterTests)

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
    auto buffer = ::binary::Allocator::Invoke([&item](auto& allocator) { ::binary::experimental::helpers::ConverterEncodeAutoMethodHelper<C>::Invoke(allocator, item); });
    return ToHex(buffer);
}

template <typename T>
std::string EncodeWithPrefixHex(const T& item) {
    using C = ::binary::experimental::Converter<T>;
    auto buffer = ::binary::Allocator::Invoke([&item](auto& allocator) { ::binary::experimental::helpers::ConverterEncodeWithLengthPrefixMethodHelper<C>::Invoke(allocator, item); });
    return ToHex(buffer);
}

template <typename T>
std::vector<std::byte> EncodeAutoBuffer(const T& item) {
    using C = ::binary::experimental::Converter<T>;
    return ::binary::Allocator::Invoke([&item](auto& allocator) { ::binary::experimental::helpers::ConverterEncodeAutoMethodHelper<C>::Invoke(allocator, item); });
}
}

BOOST_AUTO_TEST_CASE(SmartPointerConverterLengthTest) {
    BOOST_REQUIRE_EQUAL(4, ::binary::experimental::Converter<std::unique_ptr<std::int32_t>>::Length());
    BOOST_REQUIRE_EQUAL(4, ::binary::experimental::Converter<std::shared_ptr<std::int32_t>>::Length());
    BOOST_REQUIRE_EQUAL(0, ::binary::experimental::Converter<std::unique_ptr<std::string>>::Length());
    BOOST_REQUIRE_EQUAL(0, ::binary::experimental::Converter<std::shared_ptr<std::string>>::Length());
}

BOOST_AUTO_TEST_CASE(SmartPointerConverterWireTest) {
    BOOST_REQUIRE_EQUAL("05000000", EncodeHex(std::make_unique<std::int32_t>(5)));
    BOOST_REQUIRE_EQUAL("05000000", EncodeAutoHex(std::make_unique<std::int32_t>(5)));
    BOOST_REQUIRE_EQUAL("05000000", EncodeHex(std::make_shared<std::int32_t>(5)));

    BOOST_REQUIRE_EQUAL("616263", EncodeHex(std::make_unique<std::string>("abc")));
    BOOST_REQUIRE_EQUAL("03616263", EncodeAutoHex(std::make_unique<std::string>("abc")));
}

BOOST_AUTO_TEST_CASE(SmartPointerConverterPrefixTest) {
    BOOST_REQUIRE_EQUAL("0405000000", EncodeWithPrefixHex(std::make_unique<std::int32_t>(5)));
}

BOOST_AUTO_TEST_CASE(SmartPointerConverterRoundTripTest) {
    using T = std::shared_ptr<std::string>;

    auto bytes = EncodeAutoBuffer(std::make_shared<std::string>("abc"));
    std::span<const std::byte> span(bytes);
    auto first = ::binary::experimental::helpers::ConverterDecodeAutoMethodHelper<::binary::experimental::Converter<T>>::Invoke(span);
    BOOST_REQUIRE_EQUAL(0, span.size());
    BOOST_REQUIRE(first != nullptr);
    BOOST_REQUIRE_EQUAL("abc", *first);

    std::span<const std::byte> again(bytes);
    auto second = ::binary::experimental::helpers::ConverterDecodeAutoMethodHelper<::binary::experimental::Converter<T>>::Invoke(again);
    BOOST_REQUIRE(first != second);
    *second = "xyz";
    BOOST_REQUIRE_EQUAL("abc", *first);
}

BOOST_AUTO_TEST_CASE(SmartPointerConverterNullTest) {
    BOOST_REQUIRE_EXCEPTION(
        EncodeHex(std::unique_ptr<std::int32_t>()),
        std::invalid_argument,
        [](const std::invalid_argument& e) { return std::string(e.what()).starts_with("null pointer"); }
    );

    BOOST_REQUIRE_EXCEPTION(
        EncodeHex(std::shared_ptr<std::int32_t>()),
        std::invalid_argument,
        [](const std::invalid_argument& e) { return std::string(e.what()).starts_with("null pointer"); }
    );
}

BOOST_AUTO_TEST_CASE(SmartPointerConverterInContainerTest) {
    using Pointers = std::vector<std::unique_ptr<std::int32_t>>;
    using Values = std::vector<std::int32_t>;

    Pointers pointers;
    pointers.push_back(std::make_unique<std::int32_t>(1));
    pointers.push_back(std::make_unique<std::int32_t>(2));
    pointers.push_back(std::make_unique<std::int32_t>(3));

    // A container of pointers is byte equal to a container of the pointee.
    BOOST_REQUIRE_EQUAL("0c010000000200000003000000", EncodeAutoHex(pointers));
    BOOST_REQUIRE_EQUAL(EncodeAutoHex(Values{1, 2, 3}), EncodeAutoHex(pointers));

    auto bytes = ::binary::Allocator::Invoke([&pointers](auto& allocator) {
        ::binary::experimental::helpers::ConverterEncodeAutoMethodHelper<::binary::experimental::Converter<Pointers>>::Invoke(allocator, pointers);
    });
    std::span<const std::byte> span(bytes);
    auto result = ::binary::experimental::helpers::ConverterDecodeAutoMethodHelper<::binary::experimental::Converter<Pointers>>::Invoke(span);
    BOOST_REQUIRE_EQUAL(0, span.size());
    BOOST_REQUIRE_EQUAL(3, result.size());
    BOOST_REQUIRE_EQUAL(2, *result.at(1));
}

BOOST_AUTO_TEST_CASE(SmartPointerConverterVariableElementTest) {
    using Source = std::vector<std::unique_ptr<std::string>>;

    Source source;
    source.push_back(std::make_unique<std::string>("a"));
    source.push_back(std::make_unique<std::string>("b"));

    BOOST_REQUIRE_EQUAL("0401610162", EncodeAutoHex(source));
}

BOOST_AUTO_TEST_SUITE_END()
}
