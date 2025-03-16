#include <boost/test/data/test_case.hpp>
#include <boost/test/unit_test.hpp>

#include <binary/converters/ContainerConverter.hpp>
#include <binary/converters/LittleEndianConverter.hpp>
#include <binary/converters/LittleEndianStringConverter.hpp>

namespace tests::binary::converters::ContainerConverterTests {
BOOST_AUTO_TEST_SUITE(CustomNoReserveFunctionContainerTests)

template <typename T>
class CustomNoReserveFunctionContainer {
public:
    std::list<std::remove_cv_t<T>> List;

    auto end() const {
        return this->List.cend();
    }

    auto begin() const {
        return this->List.cbegin();
    }

    void emplace_back(const std::remove_cv_t<T>& item) {
        this->List.emplace_back(item);
    }
};

BOOST_AUTO_TEST_CASE(CustomNoReserveFunctionContainerEncodeDecodeNumberTypeTest) {
    CustomNoReserveFunctionContainer<int32_t> source;
    source.List = {6, 7, 8, 9, 10, 11};
    ::binary::converters::ContainerConverter<CustomNoReserveFunctionContainer<int32_t>> converter(std::make_shared<::binary::converters::LittleEndianConverter<int32_t>>());
    ::binary::Allocator allocator;
    converter.Encode(allocator, source);
    BOOST_REQUIRE_EQUAL(allocator.Length(), 24);
    auto actual = converter.Decode(allocator.AsSpan());
    BOOST_REQUIRE_EQUAL(actual.List.size(), 6);
    BOOST_REQUIRE_EQUAL_COLLECTIONS(source.List.begin(), source.List.end(), actual.List.begin(), actual.List.end());
}

BOOST_AUTO_TEST_CASE(CustomNoReserveFunctionContainerEncodeDecodeConstantModifierStringTypeTest) {
    CustomNoReserveFunctionContainer<const std::string> source;
    source.List = {"E", "F"};
    ::binary::converters::ContainerConverter<CustomNoReserveFunctionContainer<const std::string>> converter(std::make_shared<::binary::converters::LittleEndianStringConverter<std::string>>());
    ::binary::Allocator allocator;
    converter.Encode(allocator, source);
    BOOST_REQUIRE_EQUAL(allocator.Length(), 4);
    auto actual = converter.Decode(allocator.AsSpan());
    BOOST_REQUIRE_EQUAL(actual.List.size(), 2);
    BOOST_REQUIRE_EQUAL_COLLECTIONS(source.List.begin(), source.List.end(), actual.List.begin(), actual.List.end());
}

BOOST_AUTO_TEST_SUITE_END()
}
