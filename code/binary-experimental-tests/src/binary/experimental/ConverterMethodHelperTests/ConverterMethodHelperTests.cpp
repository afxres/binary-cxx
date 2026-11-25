#include <boost/mpl/list.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/unit_test.hpp>

#include <binary/experimental/Converter.hpp>
#include <binary/experimental/converters/ContainerConverter.hpp>
#include <binary/experimental/converters/LittleEndianConverter.hpp>
#include <binary/experimental/converters/LittleEndianStringConverter.hpp>
#include <binary/experimental/converters/TupleConverter.hpp>
#include <binary/experimental/converters/VariantConverter.hpp>

#include <array>
#include <cstdint>
#include <list>
#include <span>
#include <stdexcept>
#include <string>
#include <tuple>
#include <variant>
#include <vector>

namespace tests::binary::experimental::ConverterMethodHelperTests {
BOOST_AUTO_TEST_SUITE(ConverterMethodHelperTests)

BOOST_AUTO_TEST_CASE(ConverterMethodHelperDecodeAutoNotEnoughBytesTest) {
    // `int64_t` has a fixed length, so the inherited default slices it and never
    // reads past the end of the buffer.
    using ConverterType = ::binary::experimental::Converter<int64_t>;
    auto message = "not enough bytes or byte sequence invalid";
    std::array<std::byte, sizeof(int64_t)> buffer;
    std::span<const std::byte> source = buffer;
    auto a = source.subspan(1);
    auto b = source.subspan(8);
    BOOST_REQUIRE_EXCEPTION(
        ConverterType::DecodeAuto(a),
        std::length_error,
        [message](const std::length_error& e) {
            BOOST_REQUIRE_EQUAL(e.what(), message);
            return true;
        }
    );
    BOOST_REQUIRE_EXCEPTION(
        ConverterType::DecodeAuto(b),
        std::length_error,
        [message](const std::length_error& e) {
            BOOST_REQUIRE_EQUAL(e.what(), message);
            return true;
        }
    );
}

using ConverterMethodHelperEncodeWithLengthPrefixTestTypeData = boost::mpl::list<
    int32_t,
    std::string,
    std::tuple<int32_t>,
    std::variant<int16_t, std::string>,
    std::vector<int32_t>,
    std::list<std::string>>;

BOOST_AUTO_TEST_CASE_TEMPLATE(ConverterMethodHelperEncodeWithLengthPrefixTest, T, ConverterMethodHelperEncodeWithLengthPrefixTestTypeData) {
    using ConverterType = ::binary::experimental::Converter<T>;
    auto buffer = ::binary::Allocator::Invoke([](auto& allocator) { ConverterType::EncodeWithLengthPrefix(allocator, T{}); });
    std::span<const std::byte> span = buffer;
    auto result = ::binary::DecodeWithLengthPrefix(span);
    BOOST_REQUIRE_EQUAL(0, span.size());
    BOOST_REQUIRE(ConverterType::Decode(result) == T{});
}

BOOST_AUTO_TEST_SUITE_END()
}
