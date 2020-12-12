#pragma once

#include <memory>

namespace mikodev::binary
{
    class abstract_converter_interface;

    using abstract_converter_interface_ptr = std::shared_ptr<abstract_converter_interface>;

    class abstract_converter_interface
    {
    private:
        size_t length_;

    public:
        abstract_converter_interface() : abstract_converter_interface(0) {}

        abstract_converter_interface(size_t length) : length_(length) {}

        virtual ~abstract_converter_interface() {}

        size_t length() const noexcept { return length_; }
    };
}
