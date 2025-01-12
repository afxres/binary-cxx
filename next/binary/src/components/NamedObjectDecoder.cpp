#include "binary/components/NamedObjectDecoder.hpp"

#include <cassert>
#include <format>
#include <stdexcept>

#include "binary/Memory.hpp"

namespace binary::components {
NamedObjectDecoder::NamedObjectDecoder(const std::vector<bool>& optional, const std::vector<std::string>& names, const std::vector<std::vector<std::byte>>& headers)
    : optional(optional), names(names) {
    assert(headers.size() == names.size());
    assert(headers.size() == optional.size());
    for (size_t i = 0; i < headers.size(); i++) {
        const auto& head = headers.at(i);
        std::string_view view(reinterpret_cast<const char*>(head.data()), head.size());
        if (!this->record.try_emplace(view, i).second) {
            ExceptKeyFound(i);
        }
    }
}

void NamedObjectDecoder::Invoke(const std::span<const std::byte>& span, std::vector<std::tuple<bool, std::span<const std::byte>>>& slices) {
    const auto& record = this->record;
    const auto& optional = this->optional;
    slices.resize(record.size());
    std::span<const std::byte> intent = span;
    while (!intent.empty()) {
        auto head = DecodeWithLengthPrefix(intent);
        auto tail = DecodeWithLengthPrefix(intent);
        std::string_view view(reinterpret_cast<const char*>(head.data()), head.size());
        auto iterator = record.find(view);
        if (iterator == record.end()) {
            continue;
        }

        auto cursor = iterator->second;
        if (std::get<0>(slices.at(cursor))) {
            ExceptKeyFound(cursor);
        }
        slices.at(cursor) = std::make_tuple(true, tail);
    }

    for (size_t i = 0; i < slices.size(); i++) {
        if (!std::get<0>(slices.at(i)) && !optional.at(i)) {
            ExceptNotFound(i);
        }
    }
}

void NamedObjectDecoder::ExceptKeyFound(size_t index) {
    throw std::invalid_argument(std::format("named key '{}' already exists", this->names.at(index)));
}

void NamedObjectDecoder::ExceptNotFound(size_t index) {
    throw std::invalid_argument(std::format("named key '{}' does not exist", this->names.at(index)));
}
}
