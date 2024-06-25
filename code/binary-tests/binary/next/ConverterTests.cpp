#include <boost/test/unit_test.hpp>

#include "binary/next/Converter.hpp"

namespace binary::tests::ConverterTests {
template <typename T>
class FakeEmptyConverter : public binary::Converter<T> {
    virtual void Encode(Allocator& allocator, const T& item) override {
        throw std::exception();
    }

    virtual T Decode(std::span<std::byte> span) {
        throw std::exception();
    }
};

BOOST_AUTO_TEST_SUITE(ConverterTests)
BOOST_AUTO_TEST_CASE(ConverterDefaultLengthTest) {
    FakeEmptyConverter<int32_t> emptyConverter{};
    BOOST_REQUIRE_EQUAL(emptyConverter.Length(), 0);
}
BOOST_AUTO_TEST_SUITE_END()
}
