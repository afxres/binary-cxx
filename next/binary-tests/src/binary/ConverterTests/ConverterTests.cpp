#include <boost/test/data/test_case.hpp>
#include <boost/test/unit_test.hpp>

#include "binary/Converter.hpp"

namespace tests::binary::ConverterTests {
BOOST_AUTO_TEST_SUITE(ConverterTests)

using ::binary::Allocator;
using ::binary::Converter;

template <typename T>
class FakeEmptyConverter : public Converter<T> {
    using Converter<T>::Converter;

    virtual void Encode([[maybe_unused]] Allocator& allocator, [[maybe_unused]] const T& item) override {
        throw std::exception();
    }

    virtual T Decode([[maybe_unused]] const std::span<const std::byte>& span) override {
        throw std::exception();
    }
};

BOOST_AUTO_TEST_CASE(ConverterDefaultLengthTest) {
    FakeEmptyConverter<int32_t> converter{};
    BOOST_REQUIRE_EQUAL(converter.Length(), 0);
}

std::vector<size_t> ConverterCustomLengthData = {0, 1, 4, 128, 1024};

BOOST_DATA_TEST_CASE(ConverterCustomLengthTests, ConverterCustomLengthData) {
    FakeEmptyConverter<int32_t> converter{sample};
    BOOST_REQUIRE_EQUAL(converter.Length(), sample);
}

std::vector<size_t> ConverterInvalidLengthData = {0x8000'0000, 0x8000'0001, 0xFFFF'FFFF};

BOOST_DATA_TEST_CASE(ConverterInvalidLengthTest, ConverterInvalidLengthData) {
    BOOST_REQUIRE_EXCEPTION(
        FakeEmptyConverter<int32_t> ignore{sample},
        std::out_of_range,
        ([](const std::out_of_range& e) {
            BOOST_REQUIRE_EQUAL(e.what(), "length > INT32_MAX");
            return true;
        }));
}

BOOST_AUTO_TEST_SUITE_END()
}
