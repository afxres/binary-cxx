#pragma once

#include "application_exception.hpp"

namespace mikodev::binary::exceptions {
class argument_out_of_range_exception : public application_exception {
public:
    using application_exception::application_exception;
};
}
