#pragma once

#include <memory>

namespace mikodev::binary
{
    using byte_t = unsigned char;

    class span_view_base
    {
    public:
        virtual const byte_t* data() const noexcept = 0;

        virtual size_t size() const noexcept = 0;

        virtual std::unique_ptr<span_view_base> clone() const noexcept = 0;

        virtual std::unique_ptr<span_view_base> slice(size_t offset) const = 0;

        virtual std::unique_ptr<span_view_base> slice(size_t offset, size_t length) const = 0;

        virtual void slice_this(size_t offset) = 0;

        virtual void slice_this(size_t offset, size_t length) = 0;
    };
}
