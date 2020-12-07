#pragma once

namespace mikodev::binary
{
    class converter_abstract
    {
    private:
        size_t _size;

    public:
        converter_abstract() : converter_abstract(0) {}

        converter_abstract(size_t size) : _size(size) {}

        virtual ~converter_abstract() {}

        size_t size() const noexcept { return _size; }
    };
}
