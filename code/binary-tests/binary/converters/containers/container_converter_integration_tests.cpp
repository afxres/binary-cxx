#include "../../../models/test_type.hpp"
#include "../../../models/test_type_converter.hpp"

#include <boost/test/unit_test.hpp>
#include <boost/mpl/list.hpp>

#include <list>
#include <deque>
#include <vector>

#include <binary/converters/little_endian_converter.hpp>
#include <binary/converters/pair_converter.hpp>
#include <binary/converters/string_converter.hpp>
#include <binary/converters/containers/list_converter.hpp>
#include <binary/converters/containers/deque_converter.hpp>
#include <binary/converters/containers/vector_converter.hpp>
#include <binary/converters/containers/map_converter.hpp>
#include <binary/converters/containers/set_converter.hpp>
#include <binary/converters/containers/unordered_map_converter.hpp>
#include <binary/converters/containers/unordered_set_converter.hpp>
#include <binary/implementations/simple_heap_buffer.hpp>

namespace mikodev::binary::tests::converters::containers::integration_tests
{
    namespace mk = mikodev::binary;
    namespace mkc = mk::converters;
    namespace mki = mk::implementations;
    namespace mkcc = mkc::containers;

    template <typename _Container, typename _Ty>
    void __test_container_converter_length(abstract_converter_ptr<_Ty> underlying_converter)
    {
        auto new_line = "\n";
        auto converter = _Container(underlying_converter);
        BOOST_TEST_MESSAGE(new_line <<
            typeid(_Container).name() << new_line <<
            typeid(_Ty).name() << new_line <<
            "underlying converter size: " << underlying_converter->length() << new_line <<
            "container converter size : " << converter.length());
        BOOST_REQUIRE_EQUAL(0, converter.length());
    }

    BOOST_AUTO_TEST_CASE(container__length)
    {
        auto int32_converter = std::make_shared<mkc::little_endian_converter<int32_t>>();
        auto string_converter = std::make_shared<mkc::string_converter>();

        __test_container_converter_length<mkcc::set_converter<int32_t>, int32_t>(int32_converter);
        __test_container_converter_length<mkcc::list_converter<int32_t>, int32_t>(int32_converter);
        __test_container_converter_length<mkcc::deque_converter<int32_t>, int32_t>(int32_converter);
        __test_container_converter_length<mkcc::vector_converter<int32_t>, int32_t>(int32_converter);
        __test_container_converter_length<mkcc::unordered_set_converter<int32_t>, int32_t>(int32_converter);

        __test_container_converter_length<mkcc::set_converter<std::string>, std::string>(string_converter);
        __test_container_converter_length<mkcc::list_converter<std::string>, std::string>(string_converter);
        __test_container_converter_length<mkcc::deque_converter<std::string>, std::string>(string_converter);
        __test_container_converter_length<mkcc::vector_converter<std::string>, std::string>(string_converter);
        __test_container_converter_length<mkcc::unordered_set_converter<std::string>, std::string>(string_converter);

        BOOST_TEST_MESSAGE("PASS!");
    }

    BOOST_AUTO_TEST_CASE(container__vector__encode_decode)
    {
        auto source = std::vector<models::test_type>();
        source.reserve(5);
        for (size_t i = 5; i < 9; i++)
            source.push_back(models::test_type(i));
        auto converter = mkcc::vector_converter<models::test_type>(std::make_shared<models::test_type_converter>());
        auto buffer = mki::simple_heap_buffer().create(1024);
        auto allocator = mk::allocator(buffer);
        converter.encode(allocator, source);
        BOOST_REQUIRE_EQUAL(32, allocator.length());

        BOOST_TEST_MESSAGE("*** ***");

        auto view = allocator.as_span();
        BOOST_REQUIRE_EQUAL(32, view.length());
        auto result = converter.decode(view);
        BOOST_REQUIRE_EQUAL(32, view.length());
        BOOST_REQUIRE_EQUAL_COLLECTIONS(source.begin(), source.end(), result.begin(), result.end());
    }

    BOOST_AUTO_TEST_CASE(container__set__encode_decode)
    {
        auto source = std::set<models::test_type>();
        for (size_t i = 5; i < 9; i++)
            source.insert(models::test_type(i));
        auto converter = mkcc::set_converter<models::test_type>(std::make_shared<models::test_type_converter>());
        auto buffer = mki::simple_heap_buffer().create(1024);
        auto allocator = mk::allocator(buffer);
        converter.encode(allocator, source);
        BOOST_REQUIRE_EQUAL(32, allocator.length());

        BOOST_TEST_MESSAGE("*** ***");

        auto view = allocator.as_span();
        BOOST_REQUIRE_EQUAL(32, view.length());
        auto result = converter.decode(view);
        BOOST_REQUIRE_EQUAL(32, view.length());
        BOOST_REQUIRE_EQUAL_COLLECTIONS(source.begin(), source.end(), result.begin(), result.end());
    }

    BOOST_AUTO_TEST_CASE(container__unordered_set__encode_decode)
    {
        auto source = std::unordered_set<models::test_type>();
        source.reserve(5);
        for (size_t i = 5; i < 9; i++)
            source.insert(models::test_type(i));
        auto converter = mkcc::unordered_set_converter<models::test_type>(std::make_shared<models::test_type_converter>());
        auto buffer = mki::simple_heap_buffer().create(1024);
        auto allocator = mk::allocator(buffer);
        converter.encode(allocator, source);
        BOOST_REQUIRE_EQUAL(32, allocator.length());

        BOOST_TEST_MESSAGE("*** ***");

        auto view = allocator.as_span();
        BOOST_REQUIRE_EQUAL(32, view.length());
        auto result = converter.decode(view);
        BOOST_REQUIRE_EQUAL(32, view.length());
        for (const models::test_type& i : source)
            BOOST_REQUIRE(result.find(i) != result.end());
        BOOST_REQUIRE_EQUAL(source.size(), result.size());
    }

    BOOST_AUTO_TEST_CASE(container__map__encode_decode)
    {
        auto source = std::map<models::test_type, models::test_type>();
        for (size_t i = 5; i < 9; i++)
            source.insert(std::make_pair(models::test_type(i), models::test_type(i + 10)));
        auto underlying_converter = std::make_shared<models::test_type_converter>();
        auto converter = mkcc::map_converter<models::test_type, models::test_type>(underlying_converter, underlying_converter);
        auto buffer = mki::simple_heap_buffer().create(1024);
        auto allocator = mk::allocator(buffer);
        converter.encode(allocator, source);
        BOOST_REQUIRE_EQUAL(64, allocator.length());

        BOOST_TEST_MESSAGE("*** ***");

        auto view = allocator.as_span();
        BOOST_REQUIRE_EQUAL(64, view.length());
        auto result = converter.decode(view);
        BOOST_REQUIRE_EQUAL(64, view.length());
        for (const std::pair<const models::test_type, models::test_type>& pair : source)
            BOOST_REQUIRE_EQUAL(pair.second, result[pair.first]);
        BOOST_REQUIRE_EQUAL(source.size(), result.size());
    }

    BOOST_AUTO_TEST_CASE(container__unordered_map__encode_decode)
    {
        auto source = std::unordered_map<models::test_type, models::test_type>();
        source.reserve(5);
        for (size_t i = 5; i < 9; i++)
            source.insert(std::make_pair(models::test_type(i), models::test_type(i + 10)));
        auto underlying_converter = std::make_shared<models::test_type_converter>();
        auto converter = mkcc::unordered_map_converter<models::test_type, models::test_type>(underlying_converter, underlying_converter);
        auto buffer = mki::simple_heap_buffer().create(1024);
        auto allocator = mk::allocator(buffer);
        converter.encode(allocator, source);
        BOOST_REQUIRE_EQUAL(64, allocator.length());

        BOOST_TEST_MESSAGE("*** ***");

        auto view = allocator.as_span();
        BOOST_REQUIRE_EQUAL(64, view.length());
        auto result = converter.decode(view);
        BOOST_REQUIRE_EQUAL(64, view.length());
        for (const std::pair<const models::test_type, models::test_type>& pair : source)
            BOOST_REQUIRE_EQUAL(pair.second, result[pair.first]);
        BOOST_REQUIRE_EQUAL(source.size(), result.size());
    }
}
