#pragma once

#include "argument_exception.hpp"
#include "argument_null_exception.hpp"
#include "argument_out_of_range_exception.hpp"
#include "not_enough_bytes_exception.hpp"
#include "not_supported_exception.hpp"
#include "out_of_memory_exception.hpp"

#include <exception>

namespace mikodev::binary::exceptions {
class throw_helper {
private:
    throw_helper() = delete;

public:
    [[noreturn]]
    static void throw_allocator_modified() {
        throw argument_exception("allocator has been modified unexpectedly!");
    }

    [[noreturn]]
    static void throw_argument_exception() {
        throw argument_exception("argument invalid.");
    }

    [[noreturn]]
    static void throw_argument_null_exception() {
        throw argument_null_exception("argument can not be null.");
    }

    [[noreturn]]
    static void throw_argument_out_of_range_exception() {
        throw argument_out_of_range_exception("argument out of range.");
    }

    [[noreturn]]
    static void throw_capacity_limited() {
        throw argument_out_of_range_exception("maximum capacity has been reached.");
    }

    [[noreturn]]
    static void throw_not_enough_bytes() {
        throw not_enough_bytes_exception("not enough bytes.");
    }

    [[noreturn]]
    static void throw_not_supported() {
        throw not_supported_exception("not supported.");
    }

    [[noreturn]]
    static void throw_out_of_memory() {
        throw out_of_memory_exception("out of memory.");
    }
};
}
