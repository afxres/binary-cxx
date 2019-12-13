#include <boost/test/auto_unit_test.hpp>

#include <binary/allocator_helper.hpp>
#include <binary/implementations/simple_allocator.hpp>

namespace mikodev::binary::tests::implementations::simple_allocator_tests
{
    namespace mk = mikodev::binary;
    namespace mki = mk::implementations;

    BOOST_AUTO_TEST_CASE(simple_allocator__constructor__default)
    {
        auto allocator = mki::simple_allocator();
        BOOST_REQUIRE_EQUAL(0, allocator.size());
        BOOST_REQUIRE_EQUAL(0, allocator.capacity());
        BOOST_REQUIRE_EQUAL(INT32_MAX, allocator.max_capacity());
        BOOST_REQUIRE_EQUAL(nullptr, allocator.data());
    }

    BOOST_AUTO_TEST_CASE(simple_allocator__constructor__max_capacity_little_than_capacity)
    {
        size_t capacity = 20;
        auto data = std::shared_ptr<byte_t[]>(new byte_t[capacity]);
        auto allocator = mki::simple_allocator(data, capacity, 10);
        BOOST_REQUIRE_EQUAL(0, allocator.size());
        BOOST_REQUIRE_EQUAL(10, allocator.capacity());
        BOOST_REQUIRE_EQUAL(10, allocator.max_capacity());
        BOOST_REQUIRE_EQUAL(data, allocator.data());
    }

    std::unique_ptr<byte_t[]> _random_buffer(size_t size)
    {
        auto buffer = std::make_unique<byte_t[]>(size);
        for (size_t i = 0; i < size; i++)
            buffer[i] = static_cast<byte_t>(std::rand());
        return buffer;
    }

    void _append_range(size_t from, size_t to)
    {
        auto buffer = _random_buffer(to);
        for (size_t i = from; i <= to; i++)
        {
            auto allocator = mki::simple_allocator();
            BOOST_REQUIRE_EQUAL(0, allocator.size());
            BOOST_REQUIRE_EQUAL(0, allocator.capacity());
            allocator_helper::append(allocator, &buffer[0], i);
            BOOST_REQUIRE_EQUAL(i, allocator.size());
            BOOST_REQUIRE_EQUAL(to, allocator.capacity());
            BOOST_REQUIRE(memcmp(&buffer[0], &allocator.data()[0], i) == 0);
        }
    }

    BOOST_AUTO_TEST_CASE(simple_allocator__append__1_to_256)
    {
        _append_range(1, 256);
    }

    BOOST_AUTO_TEST_CASE(simple_allocator__append__257_to_1024)
    {
        _append_range(257, 1024);
    }

    BOOST_AUTO_TEST_CASE(simple_allocator__append_with_length_prefix__0_to_31)
    {
        auto limits = 31;
        auto buffer = _random_buffer(limits);
        for (size_t length = 0; length <= limits; length++)
        {
            auto allocator = mki::simple_allocator();
            auto anchor = allocator_helper::anchor_length_prefix(allocator);
            BOOST_REQUIRE_EQUAL(4, allocator.size());
            allocator_helper::append(allocator, &buffer[0], length);
            BOOST_REQUIRE_EQUAL(4 + length, allocator.size());
            allocator_helper::append_length_prefix(allocator, anchor);
            BOOST_REQUIRE_EQUAL(1 + length, allocator.size());
            if (length == 0)
                continue;
            auto number = static_cast<size_t>(allocator.data()[0]);
            BOOST_REQUIRE_EQUAL(number, length);
            BOOST_REQUIRE(memcmp(&buffer[0], &allocator.data()[1], length) == 0);
        }
    }

    BOOST_AUTO_TEST_CASE(simple_allocator__append_with_length_prefix__32_to_1024)
    {
        auto limits = 1024;
        auto buffer = _random_buffer(limits);
        for (size_t length = 32; length < limits; length++)
        {
            auto allocator = mki::simple_allocator();
            auto anchor = allocator_helper::anchor_length_prefix(allocator);
            BOOST_REQUIRE_EQUAL(4, allocator.size());
            allocator_helper::append(allocator, &buffer[0], length);
            BOOST_REQUIRE_EQUAL(4 + length, allocator.size());
            allocator_helper::append_length_prefix(allocator, anchor);
            BOOST_REQUIRE_EQUAL(4 + length, allocator.size());
            if (length == 0)
                continue;
            auto number = static_cast<size_t>(primitive_helper::decode_number(&allocator.data()[0], 4));
            BOOST_REQUIRE_EQUAL(number, length);
            BOOST_REQUIRE(memcmp(&buffer[0], &allocator.data()[4], length) == 0);
        }
    }
}
