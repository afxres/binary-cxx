#include <boost/test/data/test_case.hpp>
#include <boost/test/unit_test.hpp>

#include <binary/Allocator.hpp>

namespace tests::binary::AllocatorTests {
BOOST_AUTO_TEST_SUITE(AllocatorTests)

BOOST_AUTO_TEST_CASE(AllocatorDefaultValueTest) {
    ::binary::Allocator allocator;
    BOOST_REQUIRE_EQUAL(0, allocator.Length());
    BOOST_REQUIRE_EQUAL(0, allocator.Capacity());
    BOOST_REQUIRE_EQUAL(INT32_MAX, allocator.MaxCapacity());
    auto span = allocator.AsSpan();
    BOOST_REQUIRE_EQUAL(span.data(), nullptr);
    BOOST_REQUIRE_EQUAL(span.size(), 0);
}

BOOST_DATA_TEST_CASE(AllocatorCustomMaxCapacityTest, boost::unit_test::data::make<size_t>({0, 1, 65567, INT32_MAX}), maxCapacity) {
    ::binary::Allocator allocator(maxCapacity);
    BOOST_REQUIRE_EQUAL(0, allocator.Length());
    BOOST_REQUIRE_EQUAL(0, allocator.Capacity());
    BOOST_REQUIRE_EQUAL(maxCapacity, allocator.MaxCapacity());
    auto span = allocator.AsSpan();
    BOOST_REQUIRE_EQUAL(span.data(), nullptr);
    BOOST_REQUIRE_EQUAL(span.size(), 0);
}

BOOST_DATA_TEST_CASE(AllocatorInvalidMaxCapacityTest, boost::unit_test::data::make<size_t>({static_cast<uint32_t>(INT32_MAX) + 1, UINT32_MAX}), maxCapacity) {
    BOOST_REQUIRE_EXCEPTION(
        ::binary::Allocator allocator(maxCapacity),
        std::invalid_argument,
        [](const std::invalid_argument& e) {
            BOOST_REQUIRE_EQUAL(e.what(), "maxCapacity > INT32_MAX");
            return true;
        });
}

BOOST_DATA_TEST_CASE(AllocatorEnsureTest, boost::unit_test::data::make<size_t>({0, 1, 65567}), length) {
    ::binary::Allocator allocator;
    allocator.Ensure(length);
    BOOST_REQUIRE_GE(allocator.Capacity(), length);
    BOOST_REQUIRE_EQUAL(allocator.Length(), 0);
}

BOOST_DATA_TEST_CASE(AllocatorEnsureInvalidLengthTest, boost::unit_test::data::make<size_t>({1, 65567}) ^ boost::unit_test::data::make<size_t>({0, 65535}), length, maxCapacity) {
    ::binary::Allocator allocator(maxCapacity);
    BOOST_REQUIRE_EXCEPTION(
        allocator.Ensure(length),
        std::length_error,
        [](const std::length_error& e) {
            BOOST_REQUIRE_EQUAL(e.what(), "maximum capacity reached");
            return true;
        });
}

BOOST_DATA_TEST_CASE(AllocatorExpandTest, boost::unit_test::data::make<size_t>({0, 1, 65567}), length) {
    ::binary::Allocator allocator;
    allocator.Expand(length);
    BOOST_REQUIRE_GE(allocator.Capacity(), length);
    BOOST_REQUIRE_EQUAL(allocator.Length(), length);
}

BOOST_DATA_TEST_CASE(AllocatorAppendSpanTest, boost::unit_test::data::make<size_t>({0, 1, 65567}), length) {
    std::string source(length, ' ');
    ::binary::Allocator allocator;
    allocator.Append(std::span(reinterpret_cast<const std::byte*>(source.data()), source.size()));
    BOOST_REQUIRE_GE(allocator.Capacity(), length);
    BOOST_REQUIRE_EQUAL(allocator.Length(), length);
    auto span = allocator.AsSpan();
    std::string actual(reinterpret_cast<const char*>(span.data()), span.size());
    BOOST_REQUIRE_EQUAL(source, actual);
}

BOOST_AUTO_TEST_CASE(AllocatorAppendFunctionWithZeroLengthTest) {
    ::binary::Allocator allocator;
    allocator.Append(0, [](auto) {
        BOOST_TEST_FAIL("should not call");
    });
    BOOST_REQUIRE_EQUAL(0, allocator.Length());
    BOOST_REQUIRE_EQUAL(0, allocator.Capacity());
}

BOOST_DATA_TEST_CASE(AllocatorAppendFunctionTest, boost::unit_test::data::make<size_t>({1, 255, 65567}), length) {
    std::string source(length, ' ');
    ::binary::Allocator allocator;
    allocator.Append(length, [&source, &length](auto span) {
        BOOST_REQUIRE_EQUAL(length, span.size());
        memcpy(span.data(), source.data(), length);
    });
    BOOST_REQUIRE_GE(allocator.Capacity(), length);
    BOOST_REQUIRE_EQUAL(allocator.Length(), length);
    auto span = allocator.AsSpan();
    std::string actual(reinterpret_cast<const char*>(span.data()), span.size());
    BOOST_REQUIRE_EQUAL(source, actual);
}

BOOST_AUTO_TEST_SUITE_END()
}
