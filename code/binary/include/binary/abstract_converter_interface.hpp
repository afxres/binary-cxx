#pragma once

#include "define.hpp"
#include "exceptions/throw_helper.hpp"

#include <memory>
#include <typeindex>

namespace mikodev::binary
{
    class abstract_converter_interface;

    using abstract_converter_interface_ptr = std::shared_ptr<abstract_converter_interface>;

    class abstract_converter_interface
    {
        friend class converter;

        template <typename T>
        friend class abstract_converter;

    private:
        length_t length_;

        abstract_converter_interface(length_t length) : length_(length) {}

        virtual std::type_index argument__() = 0;

    public:
        virtual ~abstract_converter_interface() {};

        length_t length() const noexcept { return length_; }
    };
}
