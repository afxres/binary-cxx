#include <boost/endian.hpp>
#include <boost/mpl/list.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/unit_test.hpp>

#include <binary/experimental/Converter.hpp>

template <>
struct boost::test_tools::tt_detail::print_log_value<std::wstring> {
    void operator()(std::ostream& os, std::wstring const& value) {
        for (auto x : value) {
            os << ((char)x);
        }
    }
};

namespace tests::binary::experimental::converters::LittleEndianStringConverterTests {
BOOST_AUTO_TEST_SUITE(LittleEndianStringConverterTests)

template <typename T>
T LittleToNative(const std::span<const std::byte>& span) {
    T result(reinterpret_cast<const typename T::value_type*>(span.data()), span.size() / sizeof(typename T::value_type));
    for (auto& i : result) {
        boost::endian::little_to_native_inplace(i);
    }
    return result;
}

std::vector<std::string> StringTestData = {
    std::string(),
    std::string("\0\x01\0z", 4),
    std::string("Hello, world!"),
    std::string(127, 'A'),
};

BOOST_AUTO_TEST_CASE(LittleEndianStringConverterForStringLengthTest) {
    using ConverterType = ::binary::experimental::Converter<std::string>;
    std::string name = typeid(ConverterType).name();
    BOOST_REQUIRE(name.find("experimental") != 0);
    BOOST_REQUIRE(name.find("LittleEndianStringConverter") != 0);
    BOOST_REQUIRE_EQUAL(0, ConverterType::Length());
}

BOOST_DATA_TEST_CASE(LittleEndianStringConverterForStringEncodeDecodeTest, StringTestData, source) {
    auto x = ::binary::Allocator::Invoke([&source](auto& allocator) { ::binary::experimental::converters::LittleEndianStringConverter<std::string>::Encode(allocator, source); });
    auto y = ::binary::Allocator::Invoke([&source](auto& allocator) { ::binary::experimental::Converter<std::string>::Encode(allocator, source); });
    BOOST_REQUIRE_EQUAL(source, std::string(reinterpret_cast<const char*>(x.data()), x.size()));
    BOOST_REQUIRE_EQUAL(source, std::string(reinterpret_cast<const char*>(y.data()), y.size()));
    auto p = ::binary::experimental::converters::LittleEndianStringConverter<std::string>::Decode(x);
    auto q = ::binary::experimental::Converter<std::string>::Decode(x);
    BOOST_REQUIRE_EQUAL(source, p);
    BOOST_REQUIRE_EQUAL(source, q);
}

BOOST_DATA_TEST_CASE(LittleEndianStringConverterForStringEncodeWithLengthPrefixTest, StringTestData, source) {
    auto x = ::binary::Allocator::Invoke([&source](auto& allocator) { ::binary::experimental::converters::LittleEndianStringConverter<std::string>::EncodeWithLengthPrefix(allocator, source); });
    auto y = ::binary::Allocator::Invoke([&source](auto& allocator) { ::binary::experimental::Converter<std::string>::EncodeWithLengthPrefix(allocator, source); });
    BOOST_REQUIRE_EQUAL(std::string(reinterpret_cast<const char*>(x.data()), x.size()), std::string(reinterpret_cast<const char*>(y.data()), y.size()));
    auto actual = x;
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
    auto x = ::binary::Allocator::Invoke([&source](auto& allocator) { ::binary::experimental::converters::LittleEndianStringConverter<std::wstring>::Encode(allocator, source); });
    auto y = ::binary::Allocator::Invoke([&source](auto& allocator) { ::binary::experimental::Converter<std::wstring>::Encode(allocator, source); });
    BOOST_REQUIRE_EQUAL(source, LittleToNative<std::wstring>(x));
    BOOST_REQUIRE_EQUAL(source, LittleToNative<std::wstring>(y));
    auto p = ::binary::experimental::converters::LittleEndianStringConverter<std::wstring>::Decode(x);
    auto q = ::binary::experimental::Converter<std::wstring>::Decode(x);
    BOOST_REQUIRE_EQUAL(source, p);
    BOOST_REQUIRE_EQUAL(source, q);
}

BOOST_DATA_TEST_CASE(LittleEndianStringConverterForWideStringEncodeWithLengthPrefixTest, WideStringTestData, source) {
    auto x = ::binary::Allocator::Invoke([&source](auto& allocator) { ::binary::experimental::converters::LittleEndianStringConverter<std::wstring>::EncodeWithLengthPrefix(allocator, source); });
    auto y = ::binary::Allocator::Invoke([&source](auto& allocator) { ::binary::experimental::Converter<std::wstring>::EncodeWithLengthPrefix(allocator, source); });
    BOOST_REQUIRE_EQUAL(std::string(reinterpret_cast<const char*>(x.data()), x.size()), std::string(reinterpret_cast<const char*>(y.data()), y.size()));
    auto actual = x;
    size_t read;
    size_t length = ::binary::Decode(actual, read);
    BOOST_REQUIRE_EQUAL(read, 1);
    BOOST_REQUIRE_EQUAL(length, source.size() * sizeof(wchar_t));
    BOOST_REQUIRE_EQUAL(length + read, actual.size());
    BOOST_REQUIRE_EQUAL(source, LittleToNative<std::wstring>({actual.data() + read, length}));
}

BOOST_AUTO_TEST_CASE(LittleEndianStringConverterForWideStringDecodeNotEnoughBytesTest) {
    std::string source = "abc";
    std::span<const std::byte> buffer(reinterpret_cast<const std::byte*>(source.data()), source.size());
    std::string output = std::string() + "not enough bytes or byte sequence invalid, byte length: 3, type: " + typeid(std::wstring).name();
    BOOST_REQUIRE_EXCEPTION(
        ::binary::experimental::converters::LittleEndianStringConverter<std::wstring>::Decode(buffer),
        std::length_error,
        [&output](const std::length_error& e) {
            BOOST_REQUIRE_EQUAL(e.what(), output);
            return true;
        });
    BOOST_REQUIRE_EXCEPTION(
        ::binary::experimental::Converter<std::wstring>::Decode(buffer),
        std::length_error,
        [&output](const std::length_error& e) {
            BOOST_REQUIRE_EQUAL(e.what(), output);
            return true;
        });
}

BOOST_AUTO_TEST_SUITE_END()
}
