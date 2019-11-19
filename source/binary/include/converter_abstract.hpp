#pragma once

namespace mikodev::binary
{
    class converter_abstract
    {
    private:
        size_t _byte_size;

    public:
        converter_abstract(size_t byte_size) : _byte_size(byte_size) {}

        size_t byte_size() const noexcept { return _byte_size; }
    };
}
