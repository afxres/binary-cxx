#include <boost/test/data/test_case.hpp>
#include <boost/test/unit_test.hpp>

#include "binary/Converter.hpp"

namespace binary::tests::ConverterTests {
BOOST_AUTO_TEST_SUITE(ConverterTests)

template <typename T>
class FakeEmptyConverter : public binary::Converter<T> {
    using Converter<T>::Converter;

    virtual void Encode(Allocator& allocator, const T& item) override {
        throw std::exception();
    }

    virtual T Decode(std::span<std::byte> span) {
        throw std::exception();
    }
};

BOOST_AUTO_TEST_CASE(ConverterDefaultLengthTest) {
    FakeEmptyConverter<int32_t> converter{};
    BOOST_REQUIRE_EQUAL(converter.Length(), 0);
}

std::vector<int32_t> ConverterCustomLengthData = {0, 1, 4, 128, 1024};

BOOST_DATA_TEST_CASE(ConverterCustomLengthTests, ConverterCustomLengthData) {
    FakeEmptyConverter<int32_t> converter{sample};
    BOOST_REQUIRE_EQUAL(converter.Length(), sample);
}

std::vector<int32_t> ConverterInvalidLengthData = {-1, -300, -65537};

BOOST_DATA_TEST_CASE(ConverterInvalidLengthTest, ConverterInvalidLengthData) {
    BOOST_REQUIRE_EXCEPTION(
        FakeEmptyConverter<int32_t> ignore{sample},
        std::out_of_range,
        ([](const std::out_of_range& e) {
            return std::string(e.what()) == "length < 0";
        }));
}

BOOST_AUTO_TEST_SUITE_END()
}
