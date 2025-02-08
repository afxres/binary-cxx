#ifndef BINARY_INTERNAL_EXCEPTION_HPP
#define BINARY_INTERNAL_EXCEPTION_HPP

#include <typeindex>

namespace binary::internal {
[[noreturn]] void ThrowNotEnoughBytes();
[[noreturn]] void ThrowNotEnoughBytesToWrite();
[[noreturn]] void ThrowInvalidBytesWrittenValue();
[[noreturn]] void ThrowInvalidConverterType(std::type_index source, std::type_index target);
}

#endif
