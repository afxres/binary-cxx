#include <boost/test/unit_test.hpp>

#include <binary/converter.hpp>

namespace mk = mikodev::binary;
namespace mke = mk::exceptions;

namespace mikodev::binary::tests::converter_tests {
bool __converter__empty_bytes__filter(const mke::not_enough_bytes_exception& e) {
    BOOST_TEST_MESSAGE(e.what());
    return std::string(e.what()) == std::string("not enough bytes.");
}

BOOST_AUTO_TEST_CASE(converter__decode__empty_bytes) {
    mk::span span = mk::span();
    BOOST_REQUIRE_EXCEPTION(
        ([&span]() { mk::converter::decode(span); })(),
        mke::not_enough_bytes_exception,
        __converter__empty_bytes__filter);
}

BOOST_AUTO_TEST_CASE(converter__decode_with_length_prefix__empty_bytes) {
    mk::span span = mk::span();
    BOOST_REQUIRE_EXCEPTION(
        ([&span]() { mk::converter::decode_with_length_prefix(span); })(),
        mke::not_enough_bytes_exception,
        __converter__empty_bytes__filter);
}
}
