#pragma once

#include <boost/test/unit_test_log.hpp>

namespace mikodev::binary::tests::models
{
    class test_type
    {
    private:
        bool _moved;

        size_t _hash;

    public:
        test_type()
        {
            _hash = std::rand();
            _moved = false;
            BOOST_TEST_MESSAGE("default constructor, hash: " << _hash);
        }

        test_type(size_t hash)
        {
            _hash = hash;
            _moved = false;
            BOOST_TEST_MESSAGE("constructor, hash: " << _hash);
        }

        test_type(const test_type& other)
        {
            throw std::exception("invalid operation, copy constructor called!");
        }

        test_type(test_type&& other) noexcept
        {
            _hash = other._hash;
            _moved = false;
            other._moved = true;
            BOOST_TEST_MESSAGE("move, hash: " << _hash);
        }

        ~test_type()
        {
            BOOST_TEST_MESSAGE("destructor, hash: " << _hash << ", moved: " << _moved);
            _moved = false;
            _hash = 0;
        }

        size_t hash() const noexcept
        {
            BOOST_TEST_MESSAGE("property get, hash: " << _hash);
            return _hash;
        }

        bool operator==(const test_type& other) const noexcept
        {
            BOOST_TEST_MESSAGE("operator equal, hash: " << _hash << ", other: " << other._hash);
            return _hash == other._hash;
        }

        bool operator!=(const test_type& other) const noexcept
        {
            BOOST_TEST_MESSAGE("operator not equal, hash: " << _hash << ", other: " << other._hash);
            return _hash != other._hash;
        }

        bool operator<(const test_type& other) const noexcept
        {
            BOOST_TEST_MESSAGE("operator less than, hash: " << _hash << ", other: " << other._hash);
            return _hash < other._hash;
        }

        friend std::ostream& operator<<(std::ostream& out, const mikodev::binary::tests::models::test_type& other)
        {
            out << other.hash();
            return out;
        }
    };
}

template<>
struct std::hash<mikodev::binary::tests::models::test_type>
{
    size_t operator()(const mikodev::binary::tests::models::test_type& other) const noexcept
    {
        return other.hash();
    }
};
