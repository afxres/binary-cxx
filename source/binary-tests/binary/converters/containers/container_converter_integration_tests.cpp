#include <boost/test/auto_unit_test.hpp>
#include <boost/test/test_case_template.hpp>
#include <boost/mpl/list.hpp>

#include <list>
#include <deque>
#include <vector>

#include <binary/converters/native_converter.hpp>
#include <binary/converters/string_converter.hpp>
#include <binary/converters/containers/list_converter.hpp>
#include <binary/converters/containers/deque_converter.hpp>
#include <binary/converters/containers/vector_converter.hpp>
#include <binary/converters/containers/set_converter.hpp>
#include <binary/converters/containers/unordered_set_converter.hpp>

namespace mikodev::binary::tests::converters::containers::integration_tests
{
    namespace mk = mikodev::binary;
    namespace mkc = mk::converters;
    namespace mkcc = mkc::containers;

    template <typename _Container, typename _Underlying>
    void _test_container_converter_size()
    {
        auto new_line = "\n";
        auto underlying_converter = std::make_shared<_Underlying>();
        auto converter = _Container(underlying_converter);
        BOOST_TEST_MESSAGE(new_line <<
            typeid(_Container).name() << new_line <<
            typeid(_Underlying).name() << new_line <<
            "underlying converter size: " << underlying_converter->size() << new_line <<
            "container converter size : " << converter.size());
        BOOST_REQUIRE_EQUAL(0, converter.size());
    }

    BOOST_AUTO_TEST_CASE(container_converter__size)
    {
        _test_container_converter_size<mkcc::set_converter<int32_t>, mkc::native_converter<int32_t>>();
        _test_container_converter_size<mkcc::list_converter<int32_t>, mkc::native_converter<int32_t>>();
        _test_container_converter_size<mkcc::deque_converter<int32_t>, mkc::native_converter<int32_t>>();
        _test_container_converter_size<mkcc::vector_converter<int32_t>, mkc::native_converter<int32_t>>();
        _test_container_converter_size<mkcc::unordered_set_converter<int32_t>, mkc::native_converter<int32_t>>();

        _test_container_converter_size<mkcc::set_converter<std::string>, mkc::string_converter>();
        _test_container_converter_size<mkcc::list_converter<std::string>, mkc::string_converter>();
        _test_container_converter_size<mkcc::deque_converter<std::string>, mkc::string_converter>();
        _test_container_converter_size<mkcc::vector_converter<std::string>, mkc::string_converter>();
        _test_container_converter_size<mkcc::unordered_set_converter<std::string>, mkc::string_converter>();

        BOOST_TEST_MESSAGE("PASS!");
    }
}
