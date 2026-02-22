#include "SharedHeader.hpp"

#include <boost/test/unit_test.hpp>

#include <binary/Generator.hpp>
#include <binary/GeneratorExtensions.hpp>
#include <binary/converters/ContainerConverter.hpp>
#include <binary/converters/LittleEndianConverter.hpp>
#include <binary/converters/LittleEndianStringConverter.hpp>
#include <binary/converters/TupleConverter.hpp>

#include <map>

namespace tests::integration::SharedHeaderTests {
BOOST_AUTO_TEST_SUITE(SharedObjectTupleObjectConverterTests)

BOOST_AUTO_TEST_CASE(SharedObjectTupleObjectConverterIntegrationTest) {
    ::binary::Generator generator;
    ::binary::AddConverter<::binary::converters::LittleEndianConverter<int64_t>>(generator);
    ::binary::AddConverter<::binary::converters::LittleEndianStringConverter<std::string>>(generator);
    ::binary::AddConverter<::binary::converters::LittleEndianStringConverter<std::u8string>>(generator);
    ::binary::AddConverter<::binary::converters::TupleConverter<std::pair<const std::string, std::string>>>(generator);
    ::binary::AddConverter<::binary::converters::ContainerConverter<std::map<std::string, std::string>>>(generator);
    ::binary::AddConverter<SharedObjectNamedObjectConverter>(generator);
    auto a = ::binary::GetConverter<SharedObject>(generator);
    auto b = ::binary::GetConverter<std::map<std::string, std::string>>(generator);
    BOOST_REQUIRE_EQUAL(0, a->Length());
    BOOST_REQUIRE_EQUAL(0, b->Length());
    auto x = SharedObject{.Id = 0xFEFF, .Name = u8"BOM"};
    auto f = ::binary::Allocator::Invoke([&a, &x](auto& allocator) { a->Encode(allocator, x); });
    auto w = b->Decode(std::span(f.data(), f.size()));
    BOOST_REQUIRE_EQUAL(w.at("Id"), std::string("\xFF\xFE\0\0\0\0\0\0", 8));
    BOOST_REQUIRE_EQUAL(w.at("Name"), "BOM");
}

BOOST_AUTO_TEST_SUITE_END()
}
