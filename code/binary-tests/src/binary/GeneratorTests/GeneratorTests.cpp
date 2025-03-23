#include <boost/mpl/list.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/unit_test.hpp>

#include <binary/Generator.hpp>

namespace tests::binary::GeneratorTests {
BOOST_AUTO_TEST_SUITE(GeneratorTests)

using GeneratorTestTypeData = boost::mpl::list<int32_t, std::string>;

BOOST_AUTO_TEST_CASE_TEMPLATE(GeneratorGetConverterWithUnknownTypeTest, T, GeneratorTestTypeData) {
    ::binary::Generator generator;
    std::string output = std::string() + "converter not found, argument type: " + typeid(T).name();
    BOOST_REQUIRE_EXCEPTION(
        generator.GetConverter(typeid(T)),
        std::out_of_range,
        [&output](const std::out_of_range& e) {
            BOOST_REQUIRE_EQUAL(e.what(), output);
            return true;
        });
}

BOOST_AUTO_TEST_SUITE_END()
}
