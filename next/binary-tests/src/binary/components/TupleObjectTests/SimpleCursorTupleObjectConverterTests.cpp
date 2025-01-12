#include <boost/test/data/test_case.hpp>
#include <boost/test/unit_test.hpp>

#include <binary/Generator.hpp>
#include <binary/GeneratorExtensions.hpp>
#include <binary/components/TupleObject.hpp>
#include <binary/converters/LittleEndianConverter.hpp>
#include <binary/converters/StringConverter.hpp>

namespace tests::binary::components::TupleObjectTests {
BOOST_AUTO_TEST_SUITE(SimpleCursorTupleObjectConverterTests)

struct SimpleCursor {
    int32_t X;
    int32_t Y;
};

BINARY_TUPLE_OBJECT_CONVERTER(SimpleCursor, SimpleCursorTupleObjectConverter)
BINARY_TUPLE_MEMBER(X)
BINARY_TUPLE_MEMBER(Y)
BINARY_TUPLE_OBJECT_CONVERTER_END()

BOOST_AUTO_TEST_CASE(SimpleCursorTupleObjectConverterLengthTest) {
    ::binary::Generator generator;
    ::binary::AddConverter<::binary::converters::LittleEndianConverter<int32_t>>(generator);
    ::binary::AddConverter<SimpleCursorTupleObjectConverter>(generator);
    auto a = ::binary::GetConverter<SimpleCursor>(generator);
    BOOST_REQUIRE_EQUAL(typeid(SimpleCursorTupleObjectConverter).name(), typeid(*a).name());
    BOOST_REQUIRE_EQUAL(8, a->Length());
}

std::vector<std::tuple<std::string, int32_t, int32_t>> SimpleCursorTestData = {
    {std::string("\xab\x00\x00\x00\xcd\x00\x00\x00", 8), 0xab, 0xcd},
    {std::string("\x00\x33\x00\x00\x00\x44\x00\x00", 8), 0x3300, 0x4400},
};

BOOST_DATA_TEST_CASE(SimpleCursorTest, SimpleCursorTestData, buffer, x, y) {
    ::binary::Generator generator;
    ::binary::AddConverter<::binary::converters::LittleEndianConverter<int32_t>>(generator);
    ::binary::AddConverter<SimpleCursorTupleObjectConverter>(generator);
    auto a = ::binary::GetConverter<SimpleCursor>(generator);
    SimpleCursor f;
    f.X = x;
    f.Y = y;
    auto fa = ::binary::Allocator::Invoke([&](auto& allocator) { a->Encode(allocator, f); });
    auto fb = ::binary::Allocator::Invoke([&](auto& allocator) { a->EncodeAuto(allocator, f); });
    BOOST_REQUIRE_EQUAL(buffer, std::string_view(reinterpret_cast<const char*>(fa.data()), fa.size()));
    BOOST_REQUIRE_EQUAL(buffer, std::string_view(reinterpret_cast<const char*>(fb.data()), fb.size()));
    auto fr = a->Decode(fa);
    auto temp = std::span<const std::byte>(fb);
    auto fs = a->DecodeAuto(temp);
    BOOST_REQUIRE_EQUAL(x, fr.X);
    BOOST_REQUIRE_EQUAL(y, fr.Y);
    BOOST_REQUIRE_EQUAL(x, fs.X);
    BOOST_REQUIRE_EQUAL(y, fs.Y);
}

BOOST_AUTO_TEST_SUITE_END()
}
