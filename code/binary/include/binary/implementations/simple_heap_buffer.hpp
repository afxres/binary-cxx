#pragma once

#include "../abstract_buffer.hpp"

namespace mikodev::binary::implementations
{
    class simple_heap_buffer final : public abstract_buffer
    {
    private:
        byte_ptr buffer_;

        simple_heap_buffer(byte_ptr buffer, length_t length) : abstract_buffer(length), buffer_(buffer) {}

    public:
        simple_heap_buffer() : simple_heap_buffer(nullptr, 0) {}

        virtual byte_ptr buffer() override { return buffer_; }

        virtual ~simple_heap_buffer() override
        {
            if (buffer_ == nullptr)
                return;
            std::free(static_cast<void*>(buffer_));
            buffer_ = nullptr;
        }

        virtual abstract_buffer_ptr create(length_t length) override
        {
            if (length == 0)
                return std::make_shared<simple_heap_buffer>();
            byte_ptr buffer = static_cast<byte_ptr>(std::malloc(length));
            if (buffer == nullptr)
                exceptions::throw_helper::throw_out_of_memory();
            return std::shared_ptr<simple_heap_buffer>(new simple_heap_buffer(buffer, length));
        }
    };
}
