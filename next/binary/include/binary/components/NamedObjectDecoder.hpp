#ifndef BINARY_COMPONENTS_NAMEDOBJECTDECODER_HPP
#define BINARY_COMPONENTS_NAMEDOBJECTDECODER_HPP

#include <cstdint>
#include <span>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

namespace binary::components {
class NamedObjectDecoder {
public:
    NamedObjectDecoder(const std::vector<std::vector<std::byte>>& headers, const std::vector<std::string>& names, const std::vector<uint8_t>& optional);
    std::vector<std::span<const std::byte>> Invoke(const std::span<const std::byte>& span);

private:
    [[noreturn]] void ExceptKeyFound(size_t index);
    [[noreturn]] void ExceptNotFound(size_t index);

    const std::vector<uint8_t>& optional;
    const std::vector<std::string>& names;
    std::unordered_map<std::string_view, size_t> record;
};
}

#endif
