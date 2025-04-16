#ifndef BINARY_INTERNAL_EXCEPTION_HPP
#define BINARY_INTERNAL_EXCEPTION_HPP

#include <cstddef>
#include <typeindex>

namespace binary::internal {
[[noreturn]] void ThrowNotEnoughBytes();
[[noreturn]] void ThrowNotEnoughBytesToWrite();
[[noreturn]] void ThrowInvalidBytesWrittenValue();
[[noreturn]] void ThrowInvalidConverterType(std::type_index source, std::type_index target);
[[noreturn]] void ThrowInvalidVariantIndex(size_t index);
[[noreturn]] void ThrowConverterLengthOverflow();
[[noreturn]] void ThrowNoSuitableEmplaceMethod(std::type_index container);
}

#endif
