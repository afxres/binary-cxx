#include <boost/test/unit_test.hpp>

#include <binary/abstract_converter.hpp>

namespace mk = mikodev::binary;

namespace mikodev::binary::tests::abstract_converter_interface_tests
{
    template <typename T>
    class fake_converter : public abstract_converter<T>
    {
    public:
        using abstract_converter<T>::abstract_converter;

        virtual void encode(allocator& allocator, const T& item) override { throw std::exception(); }

        virtual T decode(const span& span) override { throw std::exception(); }
    };

    BOOST_AUTO_TEST_CASE(abstract_converter__constructor__default)
    {
        fake_converter<int> converter = fake_converter<int>();
        BOOST_REQUIRE_EQUAL(converter.length(), 0);
    }

    BOOST_AUTO_TEST_CASE(abstract_converter__constructor__length)
    {
        std::vector<length_t> vector = { 0, 1, 4, std::numeric_limits<int32_t>::max() };
        for (length_t i : vector)
        {
            fake_converter<int> converter = fake_converter<int>(i);
            BOOST_REQUIRE_EQUAL(converter.length(), i);
        }
    }
}
