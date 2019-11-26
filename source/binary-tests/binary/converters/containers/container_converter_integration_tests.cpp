#include "../../../models/test_type.hpp"
#include "../../../models/test_type_converter.hpp"

#include <boost/test/auto_unit_test.hpp>
#include <boost/test/test_case_template.hpp>
#include <boost/mpl/list.hpp>

#include <list>
#include <deque>
#include <vector>

#include <binary/converters/native_converter.hpp>
#include <binary/converters/pair_converter.hpp>
#include <binary/converters/string_converter.hpp>
#include <binary/converters/containers/list_converter.hpp>
#include <binary/converters/containers/deque_converter.hpp>
#include <binary/converters/containers/vector_converter.hpp>
#include <binary/converters/containers/set_converter.hpp>
#include <binary/converters/containers/unordered_map_converter.hpp>
#include <binary/converters/containers/unordered_set_converter.hpp>
#include <binary/converters/containers/map_converter.hpp>
#include <binary/implementations/simple_allocator.hpp>

namespace mikodev::binary::tests::converters::containers::integration_tests
{
    namespace mk = mikodev::binary;
    namespace mki = mk::implementations;
    namespace mkc = mk::converters;
    namespace mkcc = mkc::containers;

    template <typename _Container, typename _Ty>
    void _test_container_converter_size(std::shared_ptr<converter_base<_Ty>> underlying_converter)
    {
        auto new_line = "\n";
        auto converter = _Container(underlying_converter);
        BOOST_TEST_MESSAGE(new_line <<
            typeid(_Container).name() << new_line <<
            typeid(_Ty).name() << new_line <<
            "underlying converter size: " << underlying_converter->size() << new_line <<
            "container converter size : " << converter.size());
        BOOST_REQUIRE_EQUAL(0, converter.size());
    }

    BOOST_AUTO_TEST_CASE(container__size)
    {
        auto int32_converter = std::make_shared<mkc::native_converter<int32_t>>();
        auto string_converter = std::make_shared<mkc::string_converter>();

        _test_container_converter_size<mkcc::set_converter<int32_t>, int32_t>(int32_converter);
        _test_container_converter_size<mkcc::list_converter<int32_t>, int32_t>(int32_converter);
        _test_container_converter_size<mkcc::deque_converter<int32_t>, int32_t>(int32_converter);
        _test_container_converter_size<mkcc::vector_converter<int32_t>, int32_t>(int32_converter);
        _test_container_converter_size<mkcc::unordered_set_converter<int32_t>, int32_t>(int32_converter);

        _test_container_converter_size<mkcc::set_converter<std::string>, std::string>(string_converter);
        _test_container_converter_size<mkcc::list_converter<std::string>, std::string>(string_converter);
        _test_container_converter_size<mkcc::deque_converter<std::string>, std::string>(string_converter);
        _test_container_converter_size<mkcc::vector_converter<std::string>, std::string>(string_converter);
        _test_container_converter_size<mkcc::unordered_set_converter<std::string>, std::string>(string_converter);

        BOOST_TEST_MESSAGE("PASS!");
    }

    BOOST_AUTO_TEST_CASE(container__vector__encode_decode)
    {
        auto source = std::vector<models::test_type>();
        source.reserve(5);
        for (size_t i = 5; i < 9; i++)
            source.push_back(models::test_type(i));
        auto converter = mkcc::vector_converter<models::test_type>(std::make_shared<models::test_type_converter>());
        auto allocator = mki::simple_allocator();
        converter.encode(allocator, source);
        BOOST_REQUIRE_EQUAL(32, allocator.size());

        BOOST_TEST_MESSAGE("*** ***");

        auto view = allocator.as_span_view();
        BOOST_REQUIRE_EQUAL(32, view.size());
        auto result = converter.decode(view);
        BOOST_REQUIRE_EQUAL(32, view.size());
        BOOST_REQUIRE_EQUAL_COLLECTIONS(source.begin(), source.end(), result.begin(), result.end());
    }

    BOOST_AUTO_TEST_CASE(container__set__encode_decode)
    {
        auto source = std::set<models::test_type>();
        for (size_t i = 5; i < 9; i++)
            source.insert(models::test_type(i));
        auto converter = mkcc::set_converter<models::test_type>(std::make_shared<models::test_type_converter>());
        auto allocator = mki::simple_allocator();
        converter.encode(allocator, source);
        BOOST_REQUIRE_EQUAL(32, allocator.size());

        BOOST_TEST_MESSAGE("*** ***");

        auto view = allocator.as_span_view();
        BOOST_REQUIRE_EQUAL(32, view.size());
        auto result = converter.decode(view);
        BOOST_REQUIRE_EQUAL(32, view.size());
        BOOST_REQUIRE_EQUAL_COLLECTIONS(source.begin(), source.end(), result.begin(), result.end());
    }

    BOOST_AUTO_TEST_CASE(container__unordered_set__encode_decode)
    {
        auto source = std::unordered_set<models::test_type>();
        source.reserve(5);
        for (size_t i = 5; i < 9; i++)
            source.insert(models::test_type(i));
        auto converter = mkcc::unordered_set_converter<models::test_type>(std::make_shared<models::test_type_converter>());
        auto allocator = mki::simple_allocator();
        converter.encode(allocator, source);
        BOOST_REQUIRE_EQUAL(32, allocator.size());

        BOOST_TEST_MESSAGE("*** ***");

        auto view = allocator.as_span_view();
        BOOST_REQUIRE_EQUAL(32, view.size());
        auto result = converter.decode(view);
        BOOST_REQUIRE_EQUAL(32, view.size());
        BOOST_REQUIRE_EQUAL_COLLECTIONS(source.begin(), source.end(), result.begin(), result.end());
    }

    BOOST_AUTO_TEST_CASE(container__map__encode_decode)
    {
        auto source = std::map<models::test_type, models::test_type>();
        for (size_t i = 5; i < 9; i++)
            source.insert(std::make_pair(models::test_type(i), models::test_type(i + 10)));
        auto underlying_converter = std::make_shared<models::test_type_converter>();
        auto converter = mkcc::map_converter<models::test_type, models::test_type>(underlying_converter, underlying_converter);
        auto allocator = mki::simple_allocator();
        converter.encode(allocator, source);
        BOOST_REQUIRE_EQUAL(64, allocator.size());

        BOOST_TEST_MESSAGE("*** ***");

        auto view = allocator.as_span_view();
        BOOST_REQUIRE_EQUAL(64, view.size());
        auto result = converter.decode(view);
        BOOST_REQUIRE_EQUAL(64, view.size());
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
        auto allocator = mki::simple_allocator();
        converter.encode(allocator, source);
        BOOST_REQUIRE_EQUAL(64, allocator.size());

        BOOST_TEST_MESSAGE("*** ***");

        auto view = allocator.as_span_view();
        BOOST_REQUIRE_EQUAL(64, view.size());
        auto result = converter.decode(view);
        BOOST_REQUIRE_EQUAL(64, view.size());
        for (const std::pair<const models::test_type, models::test_type>& pair : source)
            BOOST_REQUIRE_EQUAL(pair.second, result[pair.first]);
        BOOST_REQUIRE_EQUAL(source.size(), result.size());
    }
}
