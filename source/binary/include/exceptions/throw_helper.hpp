#pragma once

#include "argument_exception.hpp"
#include "not_supported_exception.hpp"
#include "not_enough_bytes_exception.hpp"

#include <exception>

namespace mikodev::binary::exceptions
{
    class throw_helper
    {
    private:
        throw_helper() = delete;

    public:
        [[noreturn]] static void throw_argument_exception() { throw argument_exception("invalid argument."); }

        [[noreturn]] static void throw_not_supported() { throw not_supported_exception("not supported or not implemented."); }

        [[noreturn]] static void throw_not_enough_bytes() { throw not_enough_bytes_exception("not enough bytes."); }

        [[noreturn]] static void throw_capacity_limited() { throw std::exception("maximum capacity has been reached."); }
    };
}
