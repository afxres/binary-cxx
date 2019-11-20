#pragma once

#include <exception>
#include <string>

namespace mikodev::binary::exceptions
{
    class not_enough_bytes_exception : public std::exception
    {
    public:
        using exception::exception;
    };
}
