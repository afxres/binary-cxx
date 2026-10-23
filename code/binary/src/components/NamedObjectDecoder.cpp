#include "binary/components/NamedObjectDecoder.hpp"

#include <algorithm>
#include <cassert>
#include <format>
#include <stdexcept>

#include "binary/ConverterExtensions.hpp"
#include "binary/external/BinaryObject.hpp"

namespace binary::components {
NamedObjectDecoder::NamedObjectDecoder(const std::vector<std::vector<std::byte>>& headers, const std::vector<std::string>& names, const std::vector<uint8_t>& optional)
    : optional(optional), names(names) {
    if (headers.empty() || names.empty() || optional.empty()) {
        throw std::invalid_argument("sequence is empty");
    }
    if (headers.size() != names.size() || headers.size() != optional.size()) {
        throw std::invalid_argument("sequence lengths not match");
    }
    auto [code, list] = external::CreateByteViewList(headers);
    if (code != SIZE_MAX) {
        ExceptKeyFound(code);
    } else {
        this->record = std::move(list);
    }
}

void NamedObjectDecoder::Invoke(std::span<const std::byte> span, std::span<std::span<const std::byte>> slices) {
    const auto& record = this->record;
    const auto& optional = this->optional;
    assert(slices.size() == optional.size());
    std::fill(slices.begin(), slices.end(), std::span<const std::byte>{});
    std::span<const std::byte> copy = span;
    while (!copy.empty()) {
        auto head = DecodeWithLengthPrefix(copy);
        auto tail = DecodeWithLengthPrefix(copy);
        std::string_view view(reinterpret_cast<const char*>(head.data()), head.size());
        auto cursor = record->Invoke(head);
        if (cursor == SIZE_MAX) {
            continue;
        }
        auto& intent = slices[cursor];
        if (intent.data() != nullptr) {
            ExceptKeyFound(cursor);
        }
        intent = tail;
    }

    for (size_t i = 0; i < slices.size(); i++) {
        if (slices[i].data() == nullptr && optional.at(i) == 0) {
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
