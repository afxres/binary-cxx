#include <boost/mpl/list.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/unit_test.hpp>

#include <binary/converters/LittleEndianStringConverter.hpp>

template <>
struct boost::test_tools::tt_detail::print_log_value<std::wstring> {
    void operator()(std::ostream& os, std::wstring const& value) {
        for (auto x : value) {
            os << ((char)x);
        }
    }
};

namespace tests::binary::converters::LittleEndianStringConverterTests {
BOOST_AUTO_TEST_SUITE(LittleEndianStringConverterTests)

std::vector<std::string> StringTestData = {
    std::string(),
    std::string("\0\x01\0z", 4),
    std::string("Hello, world!"),
    std::string(127, 'A'),
};

BOOST_DATA_TEST_CASE(LittleEndianStringConverterForStringEncodeDecodeTest, StringTestData, source) {
    auto a = ::binary::converters::LittleEndianStringConverter<std::string>();
    auto x = ::binary::Allocator::Invoke([&a, &source](auto& allocator) { a.Encode(allocator, source); });
    BOOST_REQUIRE_EQUAL(source, std::string(reinterpret_cast<const char*>(x.data()), x.size()));
    auto p = a.Decode(x);
    BOOST_REQUIRE_EQUAL(source, p);
}

BOOST_DATA_TEST_CASE(LittleEndianStringConverterForStringAutoMethodsAndLengthPrefixMethodsTest, StringTestData, source) {
    auto converter = ::binary::converters::LittleEndianStringConverter<std::string>();
    ::binary::Allocator a;
    ::binary::Allocator b;
    converter.EncodeAuto(a, source);
    converter.EncodeWithLengthPrefix(b, source);
    auto x = a.AsSpan();
    auto y = b.AsSpan();
    BOOST_REQUIRE_EQUAL(std::string(reinterpret_cast<const char*>(x.data()), x.size()), std::string(reinterpret_cast<const char*>(y.data()), y.size()));
    auto i = converter.DecodeAuto(x);
    auto j = converter.DecodeWithLengthPrefix(y);
    BOOST_REQUIRE_EQUAL(source, i);
    BOOST_REQUIRE_EQUAL(source, j);
    BOOST_REQUIRE_EQUAL(0, x.size());
    BOOST_REQUIRE_EQUAL(0, y.size());
    auto actual = a.AsSpan();
    size_t read;
    size_t length = ::binary::Decode(actual, read);
    BOOST_REQUIRE_EQUAL(read, 1);
    BOOST_REQUIRE_EQUAL(length, source.size());
    BOOST_REQUIRE_EQUAL(length + read, actual.size());
    BOOST_REQUIRE_EQUAL(source, std::string(reinterpret_cast<const char*>(actual.data() + read), length));
}

std::vector<std::wstring> WideStringTestData = {
    std::wstring(),
    std::wstring(L"\0Z\0\x02", 4),
    std::wstring(L"Hello, world!"),
    std::wstring(127 / sizeof(wchar_t), L'W'),
};

BOOST_DATA_TEST_CASE(LittleEndianStringConverterForWideStringEncodeDecodeTest, WideStringTestData, source) {
    auto a = ::binary::converters::LittleEndianStringConverter<std::wstring>();
    auto x = ::binary::Allocator::Invoke([&a, &source](auto& allocator) { a.Encode(allocator, source); });
    BOOST_REQUIRE_EQUAL(source, std::wstring(reinterpret_cast<const wchar_t*>(x.data()), x.size() / sizeof(wchar_t)));
    auto p = a.Decode(x);
    BOOST_REQUIRE_EQUAL(source, p);
}

BOOST_DATA_TEST_CASE(LittleEndianStringConverterForWideStringAutoMethodsAndLengthPrefixMethodsTest, WideStringTestData, source) {
    auto converter = ::binary::converters::LittleEndianStringConverter<std::wstring>();
    ::binary::Allocator a;
    ::binary::Allocator b;
    converter.EncodeAuto(a, source);
    converter.EncodeWithLengthPrefix(b, source);
    auto x = a.AsSpan();
    auto y = b.AsSpan();
    BOOST_REQUIRE_EQUAL(std::string(reinterpret_cast<const char*>(x.data()), x.size()), std::string(reinterpret_cast<const char*>(y.data()), y.size()));
    auto i = converter.DecodeAuto(x);
    auto j = converter.DecodeWithLengthPrefix(y);
    BOOST_REQUIRE_EQUAL(source, i);
    BOOST_REQUIRE_EQUAL(source, j);
    BOOST_REQUIRE_EQUAL(0, x.size());
    BOOST_REQUIRE_EQUAL(0, y.size());
    auto actual = a.AsSpan();
    size_t read;
    size_t length = ::binary::Decode(actual, read);
    BOOST_REQUIRE_EQUAL(read, 1);
    BOOST_REQUIRE_EQUAL(length, source.size() * sizeof(wchar_t));
    BOOST_REQUIRE_EQUAL(length + read, actual.size());
    BOOST_REQUIRE_EQUAL(source, std::wstring(reinterpret_cast<const wchar_t*>(actual.data() + read), length / sizeof(wchar_t)));
}

BOOST_AUTO_TEST_CASE(LittleEndianStringConverterForWideStringDecodeNotEnoughBytesTest) {
    auto a = ::binary::converters::LittleEndianStringConverter<std::wstring>();
    std::string source = "abc";
    std::span<const std::byte> buffer(reinterpret_cast<const std::byte*>(source.data()), source.size());
    std::string output = std::string() + "not enough bytes or byte sequence invalid, byte length: 3, type: " + typeid(std::wstring).name();
    BOOST_REQUIRE_EXCEPTION(
        a.Decode(buffer),
        std::length_error,
        [&output](const std::length_error& e) {
            BOOST_REQUIRE_EQUAL(e.what(), output);
            return true;
        });
}

BOOST_AUTO_TEST_SUITE_END();
}
