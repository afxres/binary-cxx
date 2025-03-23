#include <boost/mpl/list.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/unit_test.hpp>

#include <binary/Generator.hpp>
#include <binary/components/TupleObject.hpp>
#include <binary/converters/LittleEndianConverter.hpp>
#include <binary/converters/LittleEndianStringConverter.hpp>

namespace tests::binary::components::TupleObjectTests {
BOOST_AUTO_TEST_SUITE(TemplateTypeTupleObjectConverterTests)

using BoxConverterTestTypeData = boost::mpl::list<int32_t, std::string>;

template <typename T>
struct Box {
    T Item;
};

template <typename T>
BINARY_TUPLE_OBJECT_CONVERTER(BoxConverter, Box<T>)
BINARY_TUPLE_MEMBER(Item);
BINARY_TUPLE_OBJECT_CONVERTER_END()

BOOST_AUTO_TEST_CASE_TEMPLATE(TemplateBoxTupleObjectConverterTest, T, BoxConverterTestTypeData) {
    ::binary::Generator generator;
    ::binary::AddConverter<::binary::converters::LittleEndianConverter<int32_t>>(generator);
    ::binary::AddConverter<::binary::converters::LittleEndianStringConverter<std::string>>(generator);
    ::binary::AddConverter<BoxConverter<T>>(generator);
    auto converter = ::binary::GetConverter<Box<T>>(generator);
    BOOST_REQUIRE_EQUAL(converter->Length(), ::binary::GetConverter<T>(generator)->Length());
    Box<T> source;
    source.Item = {};
    auto buffer = ::binary::Allocator::Invoke([&converter, &source](auto& allocator) { converter->Encode(allocator, source); });
    auto result = converter->Decode(buffer);
    BOOST_REQUIRE_EQUAL(result.Item, T{});
}

BOOST_AUTO_TEST_SUITE_END()
}
