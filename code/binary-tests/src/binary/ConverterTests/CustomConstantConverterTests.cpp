#include <boost/test/data/test_case.hpp>
#include <boost/test/unit_test.hpp>

#include <memory>

#include <binary/Converter.hpp>

namespace tests::binary::ConverterTests {
BOOST_AUTO_TEST_SUITE(CustomConstantConverterTests)

using ::binary::Allocator;
using ::binary::Converter;

class CustomConstantConverter : public Converter<int8_t> {
    using Converter::Converter;

    virtual void Encode(Allocator& allocator, const int8_t& item) override {
        size_t length = Length();
        auto buffer = std::make_unique<std::byte[]>(length);
        std::span<std::byte> span(buffer.get(), length);
        span[0] = static_cast<std::byte>(item);
        allocator.Append(span);
    }

    virtual int8_t Decode(const std::span<const std::byte>& span) override {
        return static_cast<int8_t>(span[0]);
    }
};

std::vector<std::tuple<size_t, int8_t>> CustomConstantConverterEncodeAutoDecodeAutoData = {
    {1, 0x77},
    {8, 0x6A},
};

BOOST_DATA_TEST_CASE(CustomConstantConverterEncodeAutoDecodeAutoTest, CustomConstantConverterEncodeAutoDecodeAutoData, converterLength, data) {
    CustomConstantConverter converter(converterLength);
    Allocator allocator;
    BOOST_REQUIRE_EQUAL(allocator.Length(), 0);
    BOOST_REQUIRE_EQUAL(converter.Length(), converterLength);
    converter.EncodeAuto(allocator, data);
    BOOST_REQUIRE_EQUAL(allocator.Length(), converterLength);
    std::span<const std::byte> span = allocator.AsSpan();
    BOOST_REQUIRE_EQUAL(span.size(), converterLength);
    BOOST_REQUIRE_EQUAL(static_cast<int8_t>(span[0]), data);

    int8_t result = converter.DecodeAuto(span);
    BOOST_REQUIRE_EQUAL(result, data);
    BOOST_REQUIRE_EQUAL(span.size(), 0);
}

BOOST_AUTO_TEST_SUITE_END()
}
