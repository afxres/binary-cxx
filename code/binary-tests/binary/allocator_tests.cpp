#include <boost/test/unit_test.hpp>

#include <binary/allocator.hpp>
#include <binary/implementations/simple_c_buffer.hpp>

#include <string>

namespace mk = mikodev::binary;
namespace mke = mk::exceptions;
namespace mki = mk::implementations;

namespace mikodev::binary::tests::allocator_tests
{
    BOOST_AUTO_TEST_CASE(allocator__constructor__buffer)
    {
        for (length_t i = 0; i <= 1024; i++)
        {
            mk::abstract_buffer_ptr buffer = mki::simple_c_buffer().create(i);
            mk::allocator allocator(buffer);
            BOOST_REQUIRE_EQUAL(allocator.length(), 0);
            BOOST_REQUIRE_EQUAL(allocator.capacity(), i);
            BOOST_REQUIRE_EQUAL(allocator.max_capacity(), std::numeric_limits<int32_t>::max());
        }
    }

    bool __constructor__buffer_null__filter(const mke::argument_null_exception& e)
    {
        BOOST_TEST_MESSAGE(e.what());
        return std::string(e.what()) == std::string("argument can not be null.");
    }

    BOOST_AUTO_TEST_CASE(allocator__constructor__buffer_null)
    {
        BOOST_REQUIRE_EXCEPTION(
            ([]() { mk::allocator allocator(nullptr); })(),
            mke::argument_null_exception,
            __constructor__buffer_null__filter);
        BOOST_REQUIRE_EXCEPTION(
            ([]() { mk::allocator allocator(nullptr, 256); })(),
            mke::argument_null_exception,
            __constructor__buffer_null__filter);
    }

    bool __constructor__max_capacity_error__filter(const mke::argument_out_of_range_exception& e)
    {
        BOOST_TEST_MESSAGE(e.what());
        return std::string(e.what()) == std::string("argument out of range.");
    }

    BOOST_AUTO_TEST_CASE(allocator__constructor__max_capacity_error)
    {
        mk::abstract_buffer_ptr buffer = mki::simple_c_buffer().create(0);
        std::vector<length_t> vector = { 0x8000'0000, 0xFFFF'FFFF };
        for (length_t i : vector)
        {
            BOOST_REQUIRE_EXCEPTION(
                ([buffer, i]() { mk::allocator allocator(buffer, i); })(),
                mke::argument_out_of_range_exception,
                __constructor__max_capacity_error__filter);
        }
    }

    BOOST_AUTO_TEST_CASE(allocator__constructor__max_capacity_little_than_buffer_length)
    {
        mk::abstract_buffer_ptr buffer = mki::simple_c_buffer().create(1024);
        std::vector<length_t> vector = { 0, 128, 768 };
        for (length_t i : vector)
        {
            mk::allocator allocator(buffer, i);
            BOOST_REQUIRE_EQUAL(allocator.length(), 0);
            BOOST_REQUIRE_EQUAL(allocator.capacity(), i);
            BOOST_REQUIRE_EQUAL(allocator.max_capacity(), i);
        }
    }

    BOOST_AUTO_TEST_CASE(allocator__constructor__max_capacity_greater_than_buffer_length)
    {
        mk::abstract_buffer_ptr buffer = mki::simple_c_buffer().create(1024);
        std::vector<length_t> vector = { 4096, 32768 };
        for (length_t i : vector)
        {
            mk::allocator allocator(buffer, i);
            BOOST_REQUIRE_EQUAL(allocator.length(), 0);
            BOOST_REQUIRE_EQUAL(allocator.capacity(), buffer->length());
            BOOST_REQUIRE_EQUAL(allocator.max_capacity(), i);
        }
    }

    BOOST_AUTO_TEST_CASE(allocator__expand__with_empty_allocator)
    {
        mk::abstract_buffer_ptr buffer = mki::simple_c_buffer().create(0);
        mk::allocator allocator(buffer);
        BOOST_REQUIRE_EQUAL(allocator.length(), 0);
        BOOST_REQUIRE_EQUAL(allocator.capacity(), 0);
        BOOST_REQUIRE_EQUAL(allocator.max_capacity(), std::numeric_limits<int32_t>::max());

        mk::allocator::expand(allocator, 16);
        BOOST_REQUIRE_EQUAL(allocator.length(), 16);
        BOOST_REQUIRE_EQUAL(allocator.capacity(), 256);
        BOOST_REQUIRE_EQUAL(allocator.max_capacity(), std::numeric_limits<int32_t>::max());

        mk::allocator::expand(allocator, 64);
        BOOST_REQUIRE_EQUAL(allocator.length(), 80);
        BOOST_REQUIRE_EQUAL(allocator.capacity(), 256);
        BOOST_REQUIRE_EQUAL(allocator.max_capacity(), std::numeric_limits<int32_t>::max());

        mk::allocator::expand(allocator, 192);
        BOOST_REQUIRE_EQUAL(allocator.length(), 272);
        BOOST_REQUIRE_EQUAL(allocator.capacity(), 1024);
        BOOST_REQUIRE_EQUAL(allocator.max_capacity(), std::numeric_limits<int32_t>::max());
    }
}
