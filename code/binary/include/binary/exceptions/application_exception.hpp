#pragma once

#include <exception>
#include <string>

namespace mikodev::binary::exceptions {
class application_exception : public std::exception {
private:
    std::string what_;

public:
    application_exception(std::string&& what)
        : what_(what) {}

    application_exception(const std::string& what)
        : what_(what) {}

    virtual const char* what() const noexcept override {
        return what_.c_str();
    }
};
}
