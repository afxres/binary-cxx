#include "SharedHeader.hpp"

#include <boost/test/unit_test.hpp>

#include <binary/Generator.hpp>
#include <binary/GeneratorExtensions.hpp>
#include <binary/converters/LittleEndianConverter.hpp>
#include <binary/converters/TupleConverter.hpp>

namespace tests::integration::SharedHeaderTests {
BOOST_AUTO_TEST_SUITE(SharedIntentTupleObjectConverterTests)

BOOST_AUTO_TEST_CASE(SharedIntentTupleObjectConverterIntegrationTest) {
    ::binary::Generator generator;
    ::binary::AddConverter<::binary::converters::LittleEndianConverter<int32_t>>(generator);
    ::binary::AddConverter<::binary::converters::TupleConverter<std::tuple<int32_t, int32_t>>>(generator);
    ::binary::AddConverter<SharedIntentTupleObjectConverter>(generator);
    auto a = ::binary::GetConverter<SharedIntent>(generator);
    auto b = ::binary::GetConverter<std::tuple<int32_t, int32_t>>(generator);
    BOOST_REQUIRE_EQUAL(sizeof(int32_t) * 2, a->Length());
    BOOST_REQUIRE_EQUAL(sizeof(int32_t) * 2, b->Length());
    auto x = SharedIntent{.X = 2, .Y = 11};
    auto y = std::make_tuple(x.X, x.Y);
    auto f = ::binary::Allocator::Invoke([&a, &x](auto& allocator) { a->Encode(allocator, x); });
    auto g = ::binary::Allocator::Invoke([&b, &y](auto& allocator) { b->Encode(allocator, y); });
    BOOST_REQUIRE_EQUAL(std::string_view(reinterpret_cast<const char*>(f.data()), f.size()), std::string_view(reinterpret_cast<const char*>(g.data()), g.size()));
    BOOST_REQUIRE_EQUAL(sizeof(int32_t) * 2, f.size());
    BOOST_REQUIRE_EQUAL(sizeof(int32_t) * 2, g.size());
}

BOOST_AUTO_TEST_SUITE_END()
}
