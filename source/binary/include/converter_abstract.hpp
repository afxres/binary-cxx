#pragma once

namespace mikodev::binary
{
    class converter_abstract
    {
    private:
        size_t _size;

    public:
        converter_abstract(size_t size) : _size(size) {}

        size_t size() const noexcept { return _size; }
    };
}
