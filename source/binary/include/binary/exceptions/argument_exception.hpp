#pragma once

#include <exception>
#include <string>

namespace mikodev::binary::exceptions
{
    class argument_exception : public std::exception
    {
    public:
        using exception::exception;
    };
}
