#pragma once

#include <exception>
#include <string>

namespace mikodev::binary::exceptions
{
    class application_exception : public std::exception
    {
    private:
        std::string _what;

    public:
        using exception::exception;

        application_exception(const std::string& what) : _what(what) {}

        application_exception(std::string&& what) : _what(what) {}

        virtual const char* what() const noexcept override { return _what.c_str(); }
    };
}
