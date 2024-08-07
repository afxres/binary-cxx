#include <boost/test/data/test_case.hpp>
#include <boost/test/unit_test.hpp>

#include "binary/Converter.hpp"

namespace binary::tests::ConverterTests {
BOOST_AUTO_TEST_SUITE(CustomVariableConverterTests)

class CustomVariableConverter : public Converter<int32_t> {
    virtual void Encode(Allocator& allocator, const int32_t& item) override {
        allocator.Expand(item);
    }

    virtual int32_t Decode(const std::span<std::byte>& span) override {
        return EnsureLength(span.size());
    }
};

std::vector<std::tuple<int32_t, int32_t>> CustomVariableConverterEncodeAutoData = {
    {0, 1},
    {128, 132},
};

BOOST_DATA_TEST_CASE(CustomVariableConverterEncodeAutoTest, CustomVariableConverterEncodeAutoData, dataLength, outputLength) {
    CustomVariableConverter converter;
    Allocator allocator;
    BOOST_REQUIRE_EQUAL(allocator.Length(), 0);
    BOOST_REQUIRE_EQUAL(converter.Length(), 0);
    converter.EncodeAuto(allocator, dataLength);
    BOOST_REQUIRE_EQUAL(allocator.Length(), outputLength);
}

BOOST_AUTO_TEST_SUITE_END()
}
