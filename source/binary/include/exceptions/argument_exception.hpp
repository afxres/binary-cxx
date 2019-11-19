#pragma once

#include <exception>
#include <string>

namespace mikodev::binary::exceptions
{
    class argument_exception : public std::exception
    {
    private:
        std::string _message;

    public:
        argument_exception(std::string message) : _message(message) { }

        virtual const char* what() const noexcept override { return _message.c_str(); }
    };
}
