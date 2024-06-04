#pragma once

#include "application_exception.hpp"

namespace mikodev::binary::exceptions {
class not_supported_exception : public application_exception {
public:
    using application_exception::application_exception;
};
}
