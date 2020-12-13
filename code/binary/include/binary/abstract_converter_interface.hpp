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
        template <typename T>
        friend class abstract_converter;

    private:
        length_t length_;

        abstract_converter_interface(length_t length) : length_(length) {}

    public:
        virtual ~abstract_converter_interface() {};

        length_t length() const noexcept { return length_; }
    };
}
