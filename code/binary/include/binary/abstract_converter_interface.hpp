#pragma once

#include "define.hpp"
#include "exceptions/throw_helper.hpp"

#include <memory>

namespace mikodev::binary
{
    class abstract_converter_interface;

    using abstract_converter_interface_ptr = std::shared_ptr<abstract_converter_interface>;

    class abstract_converter_interface
    {
    private:
        length_t length_;

    public:
        abstract_converter_interface(length_t length)
        {
            if (length > length_max)
                exceptions::throw_helper::throw_argument_out_of_range_exception();
            length_ = length;
        }

        abstract_converter_interface() : abstract_converter_interface(0) {}

        virtual ~abstract_converter_interface() {}

        length_t length() const noexcept { return length_; }
    };
}
