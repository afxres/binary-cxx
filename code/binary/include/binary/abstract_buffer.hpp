#pragma once

#include "define.hpp"

#include <memory>

namespace mikodev::binary
{
    class abstract_buffer;

    using abstract_buffer_ptr = std::shared_ptr<abstract_buffer>;

    class abstract_buffer
    {
    public:
        virtual ~abstract_buffer() {}

        virtual byte_ptr buffer() = 0;

        virtual size_t length() = 0;

        virtual abstract_buffer_ptr create(size_t length) = 0;
    };
}
