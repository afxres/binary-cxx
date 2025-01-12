#pragma once

#ifndef BINARY_COMPONENTS_NAMEDOBJECTDECODER_HPP
#define BINARY_COMPONENTS_NAMEDOBJECTDECODER_HPP

#include <map>
#include <memory>
#include <span>
#include <string>
#include <string_view>
#include <tuple>
#include <vector>

namespace binary::components {
class NamedObjectDecoder {
public:
    NamedObjectDecoder(const std::vector<bool>& optional, const std::vector<std::string>& names, const std::vector<std::vector<std::byte>>& headers);
    void Invoke(const std::span<const std::byte>& span, std::vector<std::tuple<bool, std::span<const std::byte>>>& slices);

private:
    [[noreturn]] void ExceptKeyFound(size_t index);
    [[noreturn]] void ExceptNotFound(size_t index);

    const size_t required;
    const std::vector<bool>& optional;
    const std::vector<std::string>& names;
    std::map<std::string_view, size_t> record;
};
}

#endif
