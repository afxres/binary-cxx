#include <boost/test/data/test_case.hpp>
#include <boost/test/unit_test.hpp>

#include <binary/experimental/Converter.hpp>

namespace tests::binary::experimental::converters::ContainerConverterTests {
BOOST_AUTO_TEST_SUITE(CustomNoEmplaceFunctionContainerTests)

template <typename T>
class CustomNoEmplaceFunctionContainer {
private:
    std::vector<std::remove_cv_t<T>> vector;

public:
    template <typename R>
    CustomNoEmplaceFunctionContainer(R&& vector)
        : vector(std::forward<R>(vector)) {}

    auto end() const {
        return this->vector.cend();
    }

    auto begin() const {
        return this->vector.cbegin();
    }
};

BOOST_AUTO_TEST_CASE(CustomNoEmplaceFunctionContainerEncodeNumberTypeTest) {
    using ConverterType = ::binary::experimental::Converter<CustomNoEmplaceFunctionContainer<int32_t>>;
    CustomNoEmplaceFunctionContainer<int32_t> source{std::initializer_list<int32_t>{-2, -1, 0, 1, 2}};
    ::binary::Allocator allocator;
    ConverterType::Encode(allocator, source);
    BOOST_REQUIRE_EQUAL(allocator.Length(), 20);
}

BOOST_AUTO_TEST_CASE(CustomNoEmplaceFunctionContainerDecodeStringTypeNotSupportedTest) {
    using ConverterType = ::binary::experimental::Converter<CustomNoEmplaceFunctionContainer<std::string>>;
    CustomNoEmplaceFunctionContainer<std::string> source{std::vector<std::string>{}};
    std::string output = std::string() + "no suitable emplace method found, type: " + typeid(CustomNoEmplaceFunctionContainer<std::string>).name();
    BOOST_REQUIRE_EXCEPTION(
        ConverterType::Decode(std::span<const std::byte>()),
        std::logic_error,
        [&output](const std::logic_error& e) {
            BOOST_REQUIRE_EQUAL(e.what(), output);
            return true;
        });
}

BOOST_AUTO_TEST_SUITE_END()
}
