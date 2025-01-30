#include <boost/test/data/test_case.hpp>
#include <boost/test/unit_test.hpp>

#include <binary/Converter.hpp>
#include <binary/ConverterExtensions.hpp>

namespace tests::binary::ConverterTests {
BOOST_AUTO_TEST_SUITE(CustomVariableConverterTests)

using ::binary::Allocator;
using ::binary::Converter;

class CustomVariableConverter : public Converter<int32_t> {
public:
    virtual void Encode(Allocator& allocator, const int32_t& item) override {
        std::string source = std::to_string(item);
        allocator.Append(std::as_bytes(std::span(source)));
    }

    virtual int32_t Decode(const std::span<const std::byte>& span) override {
        std::string source(reinterpret_cast<const char*>(span.data()), span.size());
        return std::stoi(source);
    }
};

BOOST_AUTO_TEST_CASE(CustomVariableConverterLengthTest) {
    CustomVariableConverter converter;
    BOOST_REQUIRE_EQUAL(converter.Length(), 0);
}

std::vector<std::tuple<int32_t, std::string>> CustomVariableConverterTestData = {
    {0, "0"},
    {128, "128"},
    {65536, "65536"},
};

BOOST_DATA_TEST_CASE(CustomVariableConverterBaseMethodsTest, CustomVariableConverterTestData, data, buffer) {
    CustomVariableConverter converter;
    Allocator allocator;
    converter.Encode(allocator, data);
    auto span = allocator.AsSpan();
    BOOST_REQUIRE_EQUAL(buffer, std::string(reinterpret_cast<const char*>(span.data()), span.size()));
    auto actual = converter.Decode(span);
    BOOST_REQUIRE_EQUAL(actual, data);
}

BOOST_DATA_TEST_CASE(CustomVariableConverterAutoMethodsAndLengthPrefixMethodsTest, CustomVariableConverterTestData, data, buffer) {
    CustomVariableConverter converter;
    Allocator a;
    Allocator b;
    converter.EncodeAuto(a, data);
    converter.EncodeWithLengthPrefix(b, data);
    auto x = a.AsSpan();
    auto y = b.AsSpan();
    BOOST_REQUIRE_EQUAL(std::string(reinterpret_cast<const char*>(x.data()), x.size()), std::string(reinterpret_cast<const char*>(y.data()), y.size()));
    auto i = converter.DecodeAuto(x);
    auto j = converter.DecodeWithLengthPrefix(y);
    BOOST_REQUIRE_EQUAL(data, i);
    BOOST_REQUIRE_EQUAL(data, j);
    BOOST_REQUIRE_EQUAL(0, x.size());
    BOOST_REQUIRE_EQUAL(0, y.size());
    auto actual = a.AsSpan();
    size_t read;
    size_t length = ::binary::Decode(actual, read);
    BOOST_REQUIRE_EQUAL(length, buffer.size());
    BOOST_REQUIRE_EQUAL(length + read, actual.size());
    BOOST_REQUIRE_EQUAL(buffer, std::string(reinterpret_cast<const char*>(actual.data() + read), length));
}

BOOST_AUTO_TEST_SUITE_END()
}
