#include <boost/test/unit_test.hpp>

#include <binary/converters/little_endian_converter.hpp>
#include <binary/converters/pair_converter.hpp>
#include <binary/converters/string_converter.hpp>

namespace mikodev::binary::tests::converters::pair_converter_tests {
namespace mkc = mikodev::binary::converters;

template <typename _Ty1, typename _Ty2, typename _Cvt1, typename _Cvt2>
void __converter_length_test(length_t length_expected) {
    auto converter_1 = std::make_shared<_Cvt1>();
    auto converter_2 = std::make_shared<_Cvt2>();
    auto converter = mkc::pair_converter<_Ty1, _Ty2>(std::make_pair(converter_1, converter_2));
    BOOST_REQUIRE_EQUAL(length_expected, converter.length());
}

BOOST_AUTO_TEST_CASE(pair_converter__length) {
    __converter_length_test<int32_t, std::string, mkc::little_endian_converter<int32_t>, mkc::string_converter>(0);
    __converter_length_test<std::string, int32_t, mkc::string_converter, mkc::little_endian_converter<int32_t>>(0);
    __converter_length_test<int32_t, int64_t, mkc::little_endian_converter<int32_t>, mkc::little_endian_converter<int64_t>>(12);
}
}
