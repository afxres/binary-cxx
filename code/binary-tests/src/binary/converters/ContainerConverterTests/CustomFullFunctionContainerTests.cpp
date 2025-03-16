#include <boost/test/data/test_case.hpp>
#include <boost/test/unit_test.hpp>

#include <binary/converters/ContainerConverter.hpp>
#include <binary/converters/LittleEndianConverter.hpp>
#include <binary/converters/LittleEndianStringConverter.hpp>

namespace tests::binary::converters::ContainerConverterTests {
BOOST_AUTO_TEST_SUITE(CustomFullFunctionContainerTests)

template <typename T>
class CustomFullFunctionContainer {
public:
    size_t ReserveCalled = SIZE_MAX;
    std::vector<std::remove_cv_t<T>> Vector;

    auto end() const {
        return this->Vector.cend();
    }

    auto begin() const {
        return this->Vector.cbegin();
    }

    void emplace(const std::remove_cv_t<T>& item) {
        this->Vector.emplace_back(item);
    }

    void reserve(size_t capacity) {
        this->ReserveCalled = capacity;
        this->Vector.reserve(capacity);
    }
};

BOOST_AUTO_TEST_CASE(CustomFullFunctionContainerEncodeDecodeNumberTypeTest) {
    CustomFullFunctionContainer<int32_t> source;
    source.Vector = {1, 2, 3, 4, 5};
    ::binary::converters::ContainerConverter<CustomFullFunctionContainer<int32_t>> converter(std::make_shared<::binary::converters::LittleEndianConverter<int32_t>>());
    ::binary::Allocator allocator;
    converter.Encode(allocator, source);
    BOOST_REQUIRE_EQUAL(allocator.Length(), 20);
    auto actual = converter.Decode(allocator.AsSpan());
    BOOST_REQUIRE_EQUAL(actual.Vector.size(), 5);
    BOOST_REQUIRE_EQUAL(actual.ReserveCalled, 5);
    BOOST_REQUIRE_EQUAL_COLLECTIONS(source.Vector.begin(), source.Vector.end(), actual.Vector.begin(), actual.Vector.end());
}

BOOST_AUTO_TEST_CASE(CustomFullFunctionContainerEncodeDecodeConstantModifierStringTypeTest) {
    CustomFullFunctionContainer<const std::string> source;
    source.Vector = {"a", "b", "c"};
    ::binary::converters::ContainerConverter<CustomFullFunctionContainer<const std::string>> converter(std::make_shared<::binary::converters::LittleEndianStringConverter<std::string>>());
    ::binary::Allocator allocator;
    converter.Encode(allocator, source);
    BOOST_REQUIRE_EQUAL(allocator.Length(), 6);
    auto actual = converter.Decode(allocator.AsSpan());
    BOOST_REQUIRE_EQUAL(actual.Vector.size(), 3);
    BOOST_REQUIRE_EQUAL(actual.ReserveCalled, SIZE_MAX);
    BOOST_REQUIRE_EQUAL_COLLECTIONS(source.Vector.begin(), source.Vector.end(), actual.Vector.begin(), actual.Vector.end());
}

BOOST_AUTO_TEST_SUITE_END()
}
