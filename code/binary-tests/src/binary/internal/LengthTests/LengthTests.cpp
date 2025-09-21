#include <boost/test/data/test_case.hpp>
#include <boost/test/unit_test.hpp>

#include <binary/internal/Length.hpp>

namespace tests::binary::internal::LengthTests {
BOOST_AUTO_TEST_SUITE(LengthTests)

BOOST_AUTO_TEST_CASE(EnsureMemoryAssertFailedTest) {
    BOOST_REQUIRE_EXCEPTION(
        ::binary::internal::EnsureMemoryAccess(nullptr),
        std::runtime_error,
        [](const std::runtime_error& e) {
            BOOST_REQUIRE_EQUAL(e.what(), "invalid memory access or out of memory");
            return true;
        });
}

BOOST_AUTO_TEST_SUITE_END()
}
