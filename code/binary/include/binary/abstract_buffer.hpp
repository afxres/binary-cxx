#pragma once

#include <memory>

namespace mikodev::binary
{
    using data_t = void*;

    class abstract_buffer;

    using abstract_buffer_ptr = std::shared_ptr<abstract_buffer>;

    class abstract_buffer
    {
    public:
        virtual ~abstract_buffer() {}

        virtual data_t buffer() = 0;

        virtual size_t length() = 0;

        virtual abstract_buffer_ptr create(size_t length) = 0;
    };
}
