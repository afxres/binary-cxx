#include <boost/test/data/test_case.hpp>
#include <boost/test/unit_test.hpp>

#include <binary/components/NamedObjectDecoder.hpp>

namespace tests::binary::components::NamedObjectDecoderTests {
BOOST_AUTO_TEST_SUITE(NamedObjectDecoderTests)

BOOST_AUTO_TEST_CASE(NamedObjectDecoderArgumentEmptyTest) {
    auto check = [](const std::invalid_argument& e) {
        BOOST_REQUIRE_EQUAL(e.what(), "sequence is empty");
        return true;
    };
    BOOST_REQUIRE_EXCEPTION(::binary::components::NamedObjectDecoder({}, {{}}, {{}}), std::invalid_argument, check);
    BOOST_REQUIRE_EXCEPTION(::binary::components::NamedObjectDecoder({{}}, {}, {{}}), std::invalid_argument, check);
    BOOST_REQUIRE_EXCEPTION(::binary::components::NamedObjectDecoder({{}}, {{}}, {}), std::invalid_argument, check);
}

BOOST_AUTO_TEST_CASE(NamedObjectDecoderArgumentLengthsNotMatchTest) {
    auto check = [](const std::invalid_argument& e) {
        BOOST_REQUIRE_EQUAL(e.what(), "sequence lengths not match");
        return true;
    };
    BOOST_REQUIRE_EXCEPTION(::binary::components::NamedObjectDecoder({{}}, {{}, {}}, {{}, {}}), std::invalid_argument, check);
    BOOST_REQUIRE_EXCEPTION(::binary::components::NamedObjectDecoder({{}, {}}, {{}}, {{}, {}}), std::invalid_argument, check);
    BOOST_REQUIRE_EXCEPTION(::binary::components::NamedObjectDecoder({{}, {}}, {{}, {}}, {{}}), std::invalid_argument, check);
}

BOOST_AUTO_TEST_SUITE_END()
}
