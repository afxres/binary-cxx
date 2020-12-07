#pragma once

#include "application_exception.hpp"

namespace mikodev::binary::exceptions
{
    class out_of_memory_exception : public application_exception
    {
    public:
        using application_exception::application_exception;
    };
}
