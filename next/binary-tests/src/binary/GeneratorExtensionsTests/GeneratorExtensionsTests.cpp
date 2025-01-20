#include <boost/test/data/test_case.hpp>
#include <boost/test/unit_test.hpp>

#include <binary/GeneratorExtensions.hpp>

namespace tests::binary::GeneratorExtensionsTests {
BOOST_AUTO_TEST_SUITE(GeneratorExtensionsTests)

using ::binary::Allocator;
using ::binary::Converter;
using ::binary::IConverter;
using ::binary::IGenerator;

class FakeGenerator : public IGenerator {
private:
    std::map<std::type_index, std::shared_ptr<IConverter>>& map;

public:
    FakeGenerator(std::map<std::type_index, std::shared_ptr<IConverter>>& map)
        : map(map) {}

    virtual void AddConverter(std::shared_ptr<IConverter> converter) override {
        map.emplace(converter->GetGenericArgument(), converter);
    }

    virtual std::shared_ptr<IConverter> GetConverter(std::type_index type) const override {
        return map.at(type);
    }
};

template <typename T>
class FakeType {};

template <typename T>
class FakeConverter : public Converter<T> {
    virtual void Encode([[maybe_unused]] Allocator& allocator, [[maybe_unused]] const T& item) override {
        throw std::logic_error("");
    }

    virtual T Decode([[maybe_unused]] const std::span<const std::byte>& span) override {
        throw std::logic_error("");
    }
};

class FakeDoubleConverter : public FakeConverter<double> {};
class FakeStringConverter : public FakeConverter<std::string> {};

class FakeNonTemplateMultipleArgumentsConverter : public FakeConverter<FakeType<void>> {
private:
    int result;

public:
    FakeNonTemplateMultipleArgumentsConverter(std::shared_ptr<Converter<double>>) {
        this->result = 1;
    }

    FakeNonTemplateMultipleArgumentsConverter(std::shared_ptr<Converter<double>>, std::shared_ptr<Converter<std::string>>) {
        this->result = 2;
    }

    int Result() const {
        return this->result;
    }
};

BOOST_AUTO_TEST_CASE(GeneratorExtensionsAddNonTemplateConverterTest) {
    std::map<std::type_index, std::shared_ptr<IConverter>> converters;
    FakeGenerator generator(converters);

    generator.AddConverter(std::make_shared<FakeDoubleConverter>());
    AddConverter<FakeNonTemplateMultipleArgumentsConverter, double>(generator);
    std::shared_ptr<FakeNonTemplateMultipleArgumentsConverter> a = std::dynamic_pointer_cast<FakeNonTemplateMultipleArgumentsConverter>(converters.at(typeid(Converter<FakeType<void>>)));
    BOOST_REQUIRE_EQUAL(a->Result(), 1);
    BOOST_REQUIRE_EQUAL(converters.size(), 2);

    converters.clear();
    generator.AddConverter(std::make_shared<FakeDoubleConverter>());
    generator.AddConverter(std::make_shared<FakeStringConverter>());
    AddConverter<FakeNonTemplateMultipleArgumentsConverter, double, std::string>(generator);
    std::shared_ptr<FakeNonTemplateMultipleArgumentsConverter> b = std::dynamic_pointer_cast<FakeNonTemplateMultipleArgumentsConverter>(converters.at(typeid(Converter<FakeType<void>>)));
    BOOST_REQUIRE_EQUAL(b->Result(), 2);
    BOOST_REQUIRE_EQUAL(converters.size(), 3);
}

BOOST_AUTO_TEST_SUITE_END()
}
