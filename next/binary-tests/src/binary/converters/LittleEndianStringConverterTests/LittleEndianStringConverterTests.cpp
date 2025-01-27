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
};

BOOST_DATA_TEST_CASE(StringEncodeDecodeTest, StringTestData, source) {
    auto a = ::binary::converters::LittleEndianStringConverter<std::string>();
    auto x = ::binary::Allocator::Invoke([&a, &source](auto& allocator) { a.Encode(allocator, source); });
    BOOST_REQUIRE_EQUAL(source, std::string(reinterpret_cast<const char*>(x.data()), x.size()));
    auto p = a.Decode(x);
    BOOST_REQUIRE_EQUAL(source, p);
}

std::vector<std::wstring> WideStringTestData = {
    std::wstring(),
    std::wstring(L"\0Z\0\x02", 4),
    std::wstring(L"Hello, world!"),
};

BOOST_DATA_TEST_CASE(WithStringEncodeDecodeTest, WideStringTestData, source) {
    auto a = ::binary::converters::LittleEndianStringConverter<std::wstring>();
    auto x = ::binary::Allocator::Invoke([&a, &source](auto& allocator) { a.Encode(allocator, source); });
    BOOST_REQUIRE_EQUAL(source, std::wstring(reinterpret_cast<const wchar_t*>(x.data()), x.size() / sizeof(wchar_t)));
    auto p = a.Decode(x);
    BOOST_REQUIRE_EQUAL(source, p);
}

BOOST_AUTO_TEST_CASE(WideStringDecodeNotEnoughBytesTest) {
    auto a = ::binary::converters::LittleEndianStringConverter<std::wstring>();
    std::string source = "abc";
    std::span<const std::byte> buffer(reinterpret_cast<const std::byte*>(source.data()), source.size());
    std::string output = std::string() + "not enough bytes or byte sequence invalid, byte length: 3, type: " + typeid(std::wstring).name();
    BOOST_REQUIRE_EXCEPTION(
        a.Decode(buffer),
        std::length_error,
        ([output](const std::length_error& e) {
            BOOST_REQUIRE_EQUAL(e.what(), output);
            return true;
        }));
}

BOOST_AUTO_TEST_SUITE_END();
}
