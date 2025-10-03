#include <boost/test/data/test_case.hpp>
#include <boost/test/unit_test.hpp>

#include <binary/IGenerator.hpp>
#include <binary/components/TupleObject.hpp>
#include <binary/converters/LittleEndianConverter.hpp>

namespace tests::binary::components::TupleObjectTests {
BOOST_AUTO_TEST_SUITE(SimpleCustomTupleObjectConverterWithUnusedGeneratorTests)

struct Box {
    int32_t Item;
};

BINARY_TUPLE_OBJECT_CONVERTER(BoxConverter, Box) {
    BINARY_TUPLE_MEMBER_CUSTOM(item.Item, item.Item = std::move(result), std::make_shared<::binary::converters::LittleEndianConverter<int32_t>>());
}

class FakeGenerator : public ::binary::IGenerator {
public:
    virtual void AddConverter([[maybe_unused]] const std::shared_ptr<::binary::IConverter>& converter) override {
        throw std::exception();
    }

    virtual const std::shared_ptr<::binary::IConverter>& GetConverter([[maybe_unused]] std::type_index type) const override {
        throw std::exception();
    }
};

BOOST_AUTO_TEST_CASE(BoxCustomTupleObjectConverterWithUnusedGeneratorTest) {
    FakeGenerator generator;
    BoxConverter converter(generator);
    BOOST_REQUIRE_EQUAL(converter.Length(), sizeof(int32_t));
    Box source{.Item = 1024};
    auto buffer = ::binary::Allocator::Invoke([&converter, &source](auto& allocator) { converter.Encode(allocator, source); });
    auto result = converter.Decode(buffer);
    BOOST_REQUIRE_EQUAL(result.Item, 1024);
}

BOOST_AUTO_TEST_SUITE_END()
}
