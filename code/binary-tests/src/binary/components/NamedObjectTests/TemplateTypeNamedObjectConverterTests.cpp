#include <boost/mpl/list.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/unit_test.hpp>

#include <binary/Generator.hpp>
#include <binary/components/NamedObjectConverter.hpp>
#include <binary/converters/LittleEndianConverter.hpp>
#include <binary/converters/LittleEndianStringConverter.hpp>

namespace tests::binary::components::NamedObjectTests {
BOOST_AUTO_TEST_SUITE(TemplateTypeNamedObjectConverterTests)

using BoxConverterTestTypeData = boost::mpl::list<int32_t, std::string>;

template <typename T>
struct Box {
    T Item;
};

template <typename T>
struct BoxSchema {
    static constexpr auto Members = std::tuple{
        ::binary::components::NamedMember{"Item", &Box<T>::Item},
    };
};

template <typename T>
using BoxConverter = ::binary::components::NamedObjectConverter<Box<T>, BoxSchema<T>>;

BOOST_AUTO_TEST_CASE_TEMPLATE(TemplateBoxNamedObjectConverterTest, T, BoxConverterTestTypeData) {
    ::binary::Generator generator;
    ::binary::AddConverter<::binary::converters::LittleEndianConverter<int32_t>>(generator);
    ::binary::AddConverter<::binary::converters::LittleEndianStringConverter<std::string>>(generator);
    ::binary::AddConverter<BoxConverter<T>>(generator);
    auto converter = ::binary::GetConverter<Box<T>>(generator);
    BOOST_REQUIRE_EQUAL(converter->Length(), 0);
    Box<T> source;
    source.Item = {};
    auto buffer = ::binary::Allocator::Invoke([&converter, &source](auto& allocator) { converter->Encode(allocator, source); });
    auto result = converter->Decode(buffer);
    BOOST_REQUIRE_EQUAL(result.Item, T{});
}

BOOST_AUTO_TEST_SUITE_END()
}
