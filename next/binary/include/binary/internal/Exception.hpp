#ifndef BINARY_INTERNAL_EXCEPTION_HPP
#define BINARY_INTERNAL_EXCEPTION_HPP

namespace binary::internal {
[[noreturn]] void ThrowNotEnoughBytes();
[[noreturn]] void ThrowNotEnoughBytesToWrite();
[[noreturn]] void ThrowInvalidBytesWrittenValue();
}

#endif
