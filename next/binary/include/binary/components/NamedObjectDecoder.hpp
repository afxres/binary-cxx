#ifndef BINARY_COMPONENTS_NAMEDOBJECTDECODER_HPP
#define BINARY_COMPONENTS_NAMEDOBJECTDECODER_HPP

#include <memory>
#include <span>
#include <string>
#include <string_view>
#include <vector>

#include "binary/external/ByteViewList.hpp"

namespace binary::components {
class NamedObjectDecoder {
public:
    NamedObjectDecoder(const std::vector<bool>& optional, const std::vector<std::string>& names, const std::vector<std::vector<std::byte>>& headers);
    std::vector<std::span<const std::byte>> Invoke(const std::span<const std::byte>& span);

private:
    [[noreturn]] void ExceptKeyFound(size_t index);
    [[noreturn]] void ExceptNotFound(size_t index);

    const std::vector<bool>& optional;
    const std::vector<std::string>& names;
    std::unique_ptr<external::ByteViewList> record;
};
}

#endif
