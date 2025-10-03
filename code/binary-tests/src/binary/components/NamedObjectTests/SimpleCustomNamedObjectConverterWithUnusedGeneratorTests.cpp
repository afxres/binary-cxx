#include <boost/test/data/test_case.hpp>
#include <boost/test/unit_test.hpp>

#include <binary/IGenerator.hpp>
#include <binary/components/NamedObject.hpp>
#include <binary/converters/LittleEndianStringConverter.hpp>

namespace tests::binary::components::NamedObjectTests {
BOOST_AUTO_TEST_SUITE(SimpleCustomNamedObjectConverterWithUnusedGeneratorTests)

struct Box {
    std::string Item;
};

BINARY_NAMED_OBJECT_CONVERTER(BoxConverter, Box) {
    BINARY_NAMED_MEMBER_CUSTOM("item", false, item.Item, item.Item = std::move(result), std::make_shared<::binary::converters::LittleEndianStringConverter<std::string>>());
}

class FakeGenerator : public ::binary::IGenerator {
private:
    std::unordered_map<std::type_index, std::shared_ptr<::binary::IConverter>> converters = {
        {typeid(std::string), std::make_shared<::binary::converters::LittleEndianStringConverter<std::string>>()},
    };

public:
    virtual void AddConverter([[maybe_unused]] const std::shared_ptr<::binary::IConverter>& converter) override {
        throw std::exception();
    }

    virtual const std::shared_ptr<::binary::IConverter>& GetConverter(std::type_index type) const override {
        return converters.at(type);
    }
};

BOOST_AUTO_TEST_CASE(BoxCustomNamedObjectConverterWithUnusedGeneratorTest) {
    FakeGenerator generator;
    BoxConverter converter(generator);
    BOOST_REQUIRE_EQUAL(converter.Length(), 0);
    Box source{.Item = "32"};
    auto buffer = ::binary::Allocator::Invoke([&converter, &source](auto& allocator) { converter.Encode(allocator, source); });
    auto result = converter.Decode(buffer);
    BOOST_REQUIRE_EQUAL(result.Item, "32");
}

BOOST_AUTO_TEST_SUITE_END()
}
