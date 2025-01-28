#include <boost/test/data/test_case.hpp>
#include <boost/test/unit_test.hpp>

#include <binary/Allocator.hpp>
#include <binary/ConverterExtensions.hpp>
#include <binary/internal/AllocatorUnsafeAccessor.hpp>

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

std::vector<std::tuple<size_t, size_t>> AllocatorAppendSpanWithMaxCapacityLimitsTestData = {
    {20, 64},
    {300, 384},
};

BOOST_DATA_TEST_CASE(AllocatorAppendSpanWithMaxCapacityLimitsTest, AllocatorAppendSpanWithMaxCapacityLimitsTestData, length, maxCapacity) {
    std::string source(length, ' ');
    ::binary::Allocator allocator(maxCapacity);
    allocator.Append(std::span(reinterpret_cast<const std::byte*>(source.data()), source.size()));
    BOOST_REQUIRE_EQUAL(allocator.Length(), length);
    BOOST_REQUIRE_EQUAL(allocator.Capacity(), maxCapacity);
    BOOST_REQUIRE_EQUAL(allocator.MaxCapacity(), maxCapacity);
    auto span = allocator.AsSpan();
    std::string actual(reinterpret_cast<const char*>(span.data()), span.size());
    BOOST_REQUIRE_EQUAL(source, actual);
}

BOOST_AUTO_TEST_CASE(AllocatorAppendSpanMultipleTimesIntegrationTest) {
    std::string a(100, '1');
    std::string b(200, '2');
    std::string c(400, '4');
    ::binary::Allocator allocator;
    allocator.Append(std::span(reinterpret_cast<const std::byte*>(a.data()), a.size()));
    BOOST_REQUIRE_EQUAL(allocator.Length(), 100);
    BOOST_REQUIRE_EQUAL(allocator.Capacity(), 256);
    allocator.Append(std::span(reinterpret_cast<const std::byte*>(b.data()), b.size()));
    BOOST_REQUIRE_EQUAL(allocator.Length(), 300);
    BOOST_REQUIRE_EQUAL(allocator.Capacity(), 512);
    allocator.Append(std::span(reinterpret_cast<const std::byte*>(c.data()), c.size()));
    BOOST_REQUIRE_EQUAL(allocator.Length(), 700);
    BOOST_REQUIRE_EQUAL(allocator.Capacity(), 1024);
    auto span = allocator.AsSpan();
    auto actual = std::string(reinterpret_cast<const char*>(span.data()), span.size());
    auto wanted = a + b + c;
    BOOST_REQUIRE_EQUAL(wanted, actual);
}

BOOST_AUTO_TEST_CASE(AllocatorAppendByteIntegrationTest) {
    ::binary::Allocator allocator;
    allocator.Append(std::byte{'A'});
    BOOST_REQUIRE_EQUAL(allocator.Length(), 1);
    BOOST_REQUIRE_EQUAL(allocator.Capacity(), 256);
    std::string a(255, 'A');
    allocator.Append(std::span(reinterpret_cast<const std::byte*>(a.data()), a.size()));
    BOOST_REQUIRE_EQUAL(allocator.Length(), 256);
    BOOST_REQUIRE_EQUAL(allocator.Capacity(), 256);
    allocator.Append(std::byte{'A'});
    BOOST_REQUIRE_EQUAL(allocator.Length(), 257);
    BOOST_REQUIRE_EQUAL(allocator.Capacity(), 512);
    auto span = allocator.AsSpan();
    auto actual = std::string(reinterpret_cast<const char*>(span.data()), span.size());
    std::string wanted(257, 'A');
    BOOST_REQUIRE_EQUAL(wanted, actual);
}

BOOST_AUTO_TEST_CASE(AllocatorAppendFunctionWithMaxLengthIntegrationTest) {
    ::binary::Allocator allocator;
    allocator.Append(200, std::function<size_t(std::span<std::byte>)>([](auto span) {
        for (auto& i : span) {
            i = std::byte{'B'};
        }
        return 100;
    }));
    BOOST_REQUIRE_EQUAL(allocator.Length(), 100);
    BOOST_REQUIRE_EQUAL(allocator.Capacity(), 256);
    allocator.Append(600, std::function<size_t(std::span<std::byte>)>([](auto span) {
        for (auto& i : span) {
            i = std::byte{'C'};
        }
        return 200;
    }));
    BOOST_REQUIRE_EQUAL(allocator.Length(), 300);
    BOOST_REQUIRE_EQUAL(allocator.Capacity(), 1024);
    auto span = allocator.AsSpan();
    auto actual = std::string(reinterpret_cast<const char*>(span.data()), span.size());
    std::string wanted = std::string(100, 'B') + std::string(200, 'C');
    BOOST_REQUIRE_EQUAL(wanted, actual);
}

BOOST_AUTO_TEST_CASE(AllocatorAppendFunctionWithZeroMaxLengthTest) {
    ::binary::Allocator allocator;
    allocator.Append(0, std::function<size_t(std::span<std::byte>)>([]([[maybe_unused]] auto span) -> size_t {
        throw std::exception();
    }));
    BOOST_REQUIRE_EQUAL(allocator.Length(), 0);
    BOOST_REQUIRE_EQUAL(allocator.Capacity(), 0);
}

BOOST_DATA_TEST_CASE(AllocatorAppendFunctionWithMaxLengthIntegrationInvalidReturnValueTest, boost::unit_test::data::make<size_t>({1, 255, 1024, 65567}), length) {
    ::binary::Allocator allocator;
    BOOST_REQUIRE_EXCEPTION(
        allocator.Append(length, std::function<size_t(std::span<std::byte>)>([length]([[maybe_unused]] auto span) {
            return length + 1;
        })),
        std::logic_error,
        [](const std::logic_error& e) {
            BOOST_REQUIRE_EQUAL(e.what(), "invalid return value");
            return true;
        });
    BOOST_REQUIRE_EQUAL(allocator.Length(), 0);
    BOOST_REQUIRE_GE(allocator.Capacity(), length);
}

BOOST_DATA_TEST_CASE(AllocatorAppendWithLengthPrefixAllocatorFunctionTest, boost::unit_test::data::make<size_t>({0, 1, 255, 1024}), length) {
    std::string source(length, ' ');
    ::binary::Allocator allocator;
    allocator.AppendWithLengthPrefix([&source](auto& allocator) {
        allocator.Append(std::span(reinterpret_cast<const std::byte*>(source.data()), source.size()));
    });
    auto span = allocator.AsSpan();
    auto result = ::binary::DecodeWithLengthPrefix(span);
    BOOST_REQUIRE_EQUAL(span.size(), 0);
    auto actual = std::string(reinterpret_cast<const char*>(result.data()), result.size());
    BOOST_REQUIRE_EQUAL(source, actual);
}

BOOST_AUTO_TEST_CASE(AllocatorAppendWithLengthPrefixFunctionWithZeroMaxLengthTest) {
    ::binary::Allocator allocator;
    allocator.AppendWithLengthPrefix(0, []([[maybe_unused]] auto span) -> size_t {
        throw std::exception();
    });
    auto span = allocator.AsSpan();
    auto result = ::binary::DecodeWithLengthPrefix(span);
    BOOST_REQUIRE_EQUAL(span.size(), 0);
    BOOST_REQUIRE_EQUAL(result.size(), 0);
}

BOOST_AUTO_TEST_CASE(AllocatorAppendWithLengthPrefixFunctionWithMaxLengthIntegrationTest) {
    ::binary::Allocator allocator;
    allocator.AppendWithLengthPrefix(192, std::function<size_t(std::span<std::byte>)>([](auto span) {
        for (auto& i : span) {
            i = std::byte{'E'};
        }
        return 128;
    }));
    allocator.AppendWithLengthPrefix(768, std::function<size_t(std::span<std::byte>)>([](auto span) {
        for (auto& i : span) {
            i = std::byte{'F'};
        }
        return 256;
    }));
    auto span = allocator.AsSpan();
    auto a = ::binary::DecodeWithLengthPrefix(span);
    auto b = ::binary::DecodeWithLengthPrefix(span);
    BOOST_REQUIRE_EQUAL(span.size(), 0);
    BOOST_REQUIRE_EQUAL(std::string(128, 'E'), std::string(reinterpret_cast<const char*>(a.data()), a.size()));
    BOOST_REQUIRE_EQUAL(std::string(256, 'F'), std::string(reinterpret_cast<const char*>(b.data()), b.size()));
}

BOOST_DATA_TEST_CASE(AllocatorAppendWithLengthPrefixFunctionWithMaxLengthIntegrationInvalidReturnValueTest, boost::unit_test::data::make<size_t>({1, 255, 1024, 65567}), length) {
    ::binary::Allocator allocator;
    BOOST_REQUIRE_EXCEPTION(
        allocator.AppendWithLengthPrefix(length, std::function<size_t(std::span<std::byte>)>([length]([[maybe_unused]] auto span) {
            return length + 1;
        })),
        std::logic_error,
        [](const std::logic_error& e) {
            BOOST_REQUIRE_EQUAL(e.what(), "invalid return value");
            return true;
        });
    BOOST_REQUIRE_EQUAL(allocator.Length(), 0);
    BOOST_REQUIRE_GT(allocator.Capacity(), length);
}

std::vector<std::tuple<size_t, size_t>> AllocatorAnchorInvalidOperationTestData = {
    {0, 0},
    {0, 3},
    {3, 0},
    {381, 384},
    {384, 384},
    {385, 384},
    {static_cast<uint32_t>(INT32_MAX) + 1, 0},
};

BOOST_DATA_TEST_CASE(AllocatorAnchorInvalidOperationTest, AllocatorAnchorInvalidOperationTestData, anchor, offset) {
    ::binary::Allocator allocator;
    allocator.Expand(offset);
    BOOST_REQUIRE_EQUAL(allocator.Length(), offset);
    BOOST_REQUIRE_EXCEPTION(
        ::binary::internal::AllocatorUnsafeAccessor::FinishAnchor(allocator, anchor),
        std::logic_error,
        [](const std::logic_error& e) {
            BOOST_REQUIRE_EQUAL(e.what(), "allocator has been modified unexpectedly");
            return true;
        });
}

BOOST_AUTO_TEST_SUITE_END()
}
