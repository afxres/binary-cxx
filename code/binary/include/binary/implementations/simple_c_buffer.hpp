#pragma once

#include "../abstract_buffer.hpp"

namespace mikodev::binary::implementations
{
    class simple_c_buffer : public abstract_buffer
    {
    private:
        data_t buffer_;

        size_t length_;

        simple_c_buffer(data_t buffer, size_t length) : buffer_(buffer), length_(length) {}

    public:
        simple_c_buffer() : simple_c_buffer(nullptr, 0) {}

        simple_c_buffer(simple_c_buffer&& _) = delete;

        simple_c_buffer(const simple_c_buffer& _) = delete;

        virtual data_t buffer() override { return buffer_; }

        virtual size_t length() override { return length_; }

        virtual ~simple_c_buffer() override
        {
            if (buffer_ == nullptr)
                return;
            std::free(buffer_);
            buffer_ = nullptr;
            length_ = 0;
        }

        virtual abstract_buffer_ptr create(size_t length) override
        {
            if (length == 0)
                return std::make_shared<simple_c_buffer>();
            data_t buffer = std::malloc(length);
            if (buffer == nullptr)
                exceptions::throw_helper::throw_out_of_memory();
            return std::shared_ptr<simple_c_buffer>(new simple_c_buffer(buffer, length));
        }
    };
}
