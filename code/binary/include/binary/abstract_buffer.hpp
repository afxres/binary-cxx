#pragma once

#include "define.hpp"

#include <memory>

namespace mikodev::binary
{
    class abstract_buffer;

    using abstract_buffer_ptr = std::shared_ptr<abstract_buffer>;

    class abstract_buffer
    {
    private:
        length_t length_;

    public:
        abstract_buffer(length_t length) : length_(length) {}

        abstract_buffer(const abstract_buffer&) = delete;

        abstract_buffer(abstract_buffer&&) = delete;

        virtual ~abstract_buffer() { length_ = 0; }

        length_t length() { return length_; }

        virtual byte_ptr buffer() = 0;

        virtual abstract_buffer_ptr create(length_t length) = 0;
    };
}
