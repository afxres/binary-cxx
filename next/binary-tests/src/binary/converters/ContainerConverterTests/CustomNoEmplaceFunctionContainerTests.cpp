#include <boost/test/data/test_case.hpp>
#include <boost/test/unit_test.hpp>

#include <binary/converters/ContainerConverter.hpp>
#include <binary/converters/LittleEndianConverter.hpp>
#include <binary/converters/LittleEndianStringConverter.hpp>

namespace tests::binary::converters::ContainerConverterTests {
BOOST_AUTO_TEST_SUITE(CustomNoEmplaceFunctionContainerTests)

template <typename T>
class CustomNoEmplaceFunctionContainer {
public:
    std::vector<std::remove_cv_t<T>> Vector;

    auto end() const {
        return this->Vector.cend();
    }

    auto begin() const {
        return this->Vector.cbegin();
    }
};

BOOST_AUTO_TEST_CASE(CustomNoEmplaceFunctionContainerEncodeNumberTypeTest) {
    CustomNoEmplaceFunctionContainer<int32_t> source;
    source.Vector = {-2, -1, 0, 1, 2};
    ::binary::converters::ContainerConverter<CustomNoEmplaceFunctionContainer<int32_t>> converter(std::make_shared<::binary::converters::LittleEndianConverter<int32_t>>());
    ::binary::Allocator allocator;
    converter.Encode(allocator, source);
    BOOST_REQUIRE_EQUAL(allocator.Length(), 20);
}

BOOST_AUTO_TEST_CASE(CustomNoEmplaceFunctionContainerDecodeStringTypeNotSupportedTest) {
    CustomNoEmplaceFunctionContainer<std::string> source;
    ::binary::converters::ContainerConverter<CustomNoEmplaceFunctionContainer<std::string>> converter(std::make_shared<::binary::converters::LittleEndianStringConverter<std::string>>());
    std::string output = std::string() + "no suitable construct method found, type: " + typeid(CustomNoEmplaceFunctionContainer<std::string>).name();
    BOOST_REQUIRE_EXCEPTION(
        converter.Decode(std::span<const std::byte>()),
        std::logic_error,
        [output](const std::logic_error& e) {
            BOOST_REQUIRE_EQUAL(e.what(), output);
            return true;
        });
}

BOOST_AUTO_TEST_SUITE_END()
}
