#include "binary/components/NamedObjectDecoder.hpp"

#include <cassert>
#include <format>
#include <stdexcept>

#include "binary/Memory.hpp"

namespace binary::components {
NamedObjectDecoder::NamedObjectDecoder(const std::vector<std::string>& names, const std::vector<std::vector<std::byte>>& headers)
    : names(names) {
    assert(names.size() == headers.size());
    for (size_t i = 0; i < headers.size(); i++) {
        const auto& head = headers.at(i);
        std::string_view view(reinterpret_cast<const char*>(head.data()), head.size());
        if (this->indexes.contains(view)) {
            ExceptKeyFound(i);
        }
        this->indexes.emplace(view, i);
    }
}

void NamedObjectDecoder::Invoke(const std::span<const std::byte>& span, std::vector<std::tuple<bool, std::span<const std::byte>>>& slices) {
    const auto& indexes = this->indexes;
    size_t remain = indexes.size();
    slices.resize(remain);
    std::span<const std::byte> intent = span;
    while (!intent.empty()) {
        auto head = DecodeWithLengthPrefix(intent);
        auto tail = DecodeWithLengthPrefix(intent);
        auto iterator = indexes.find(std::string_view(reinterpret_cast<const char*>(head.data()), head.size()));
        if (iterator == indexes.end()) {
            continue;
        }

        auto cursor = iterator->second;
        if (std::get<0>(slices.at(cursor))) {
            ExceptKeyFound(cursor);
        }
        slices.at(cursor) = std::make_tuple(true, tail);
        remain--;
    }

    if (remain != 0) {
        for (size_t i = 0; i < slices.size(); i++) {
            if (!std::get<0>(slices.at(i))) {
                ExceptNotFound(i);
            }
        }
    }
}

void NamedObjectDecoder::ExceptKeyFound(size_t index) {
    throw std::invalid_argument(std::format("object key '%s' already exists", this->names.at(index)).c_str());
}

void NamedObjectDecoder::ExceptNotFound(size_t index) {
    throw std::invalid_argument(std::format("object key '%s' does not exist", this->names.at(index)).c_str());
}
}
