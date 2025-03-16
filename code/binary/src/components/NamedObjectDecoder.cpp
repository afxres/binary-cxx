#include "binary/components/NamedObjectDecoder.hpp"

#include <format>
#include <stdexcept>

#include "binary/ConverterExtensions.hpp"

namespace binary::components {
NamedObjectDecoder::NamedObjectDecoder(const std::vector<std::vector<std::byte>>& headers, const std::vector<std::string>& names, const std::vector<uint8_t>& optional)
    : optional(optional), names(names) {
    if (headers.empty() || names.empty() || optional.empty()) {
        throw std::invalid_argument("sequence is empty");
    }
    if (headers.size() != names.size() || headers.size() != optional.size()) {
        throw std::invalid_argument("sequence lengths not match");
    }
    for (size_t i = 0; i < headers.size(); i++) {
        const auto& head = headers.at(i);
        std::string_view view(reinterpret_cast<const char*>(head.data()), head.size());
        if (!this->record.try_emplace(view, i).second) {
            ExceptKeyFound(i);
        }
    }
}

std::vector<std::span<const std::byte>> NamedObjectDecoder::Invoke(const std::span<const std::byte>& span) {
    const auto& record = this->record;
    const auto& optional = this->optional;
    std::vector<std::span<const std::byte>> slices(record.size());
    std::span<const std::byte> copy = span;
    while (!copy.empty()) {
        auto head = DecodeWithLengthPrefix(copy);
        auto tail = DecodeWithLengthPrefix(copy);
        std::string_view view(reinterpret_cast<const char*>(head.data()), head.size());
        auto iterator = record.find(view);
        if (iterator == record.end()) {
            continue;
        }

        auto cursor = iterator->second;
        auto& intent = slices.at(cursor);
        if (intent.data() != nullptr) {
            ExceptKeyFound(cursor);
        }
        intent = tail;
    }

    for (size_t i = 0; i < slices.size(); i++) {
        if (slices.at(i).data() == nullptr && !optional.at(i)) {
            ExceptNotFound(i);
        }
    }
    return slices;
}

void NamedObjectDecoder::ExceptKeyFound(size_t index) {
    throw std::invalid_argument(std::format("named key '{}' already exists", this->names.at(index)));
}

void NamedObjectDecoder::ExceptNotFound(size_t index) {
    throw std::invalid_argument(std::format("named key '{}' does not exist", this->names.at(index)));
}
}
