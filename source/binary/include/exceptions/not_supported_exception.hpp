#pragma once

#include <exception>
#include <string>

namespace mikodev::binary::exceptions
{
    class not_supported_exception : public std::exception
    {
    private:
        std::string _message;

    public:
        not_supported_exception(std::string message) : _message(message) { }

        virtual const char* what() const noexcept override { return _message.c_str(); }
    };
}
