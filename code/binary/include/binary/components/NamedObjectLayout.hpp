#ifndef BINARY_COMPONENTS_NAMEDOBJECTLAYOUT_HPP
#define BINARY_COMPONENTS_NAMEDOBJECTLAYOUT_HPP

#include <array>
#include <bit>
#include <cstddef>
#include <cstdint>
#include <format>
#include <span>
#include <stdexcept>
#include <string_view>
#include <tuple>
#include <utility>

#include "binary/ConverterExtensions.hpp"

namespace binary::components {
namespace detail {
struct Slot {
    uint64_t Head;
    uint64_t Tail;
};

inline constexpr auto PackedItemCountLimit = size_t{11};
inline constexpr auto PackedItemBytesLimit = 2 * sizeof(uint64_t) - 1;

template <typename Item>
constexpr auto Load(std::string_view name, size_t offset) {
    uint64_t value = 0;
    for (size_t index = 0; index < sizeof(Item); index++) {
        value |= static_cast<uint64_t>(static_cast<unsigned char>(name[offset + index])) << (0x08U * index);
    }
    return static_cast<Item>(value);
}

constexpr auto Pack(std::string_view name) {
    using BIN1 = uint8_t;
    using BIN2 = uint16_t;
    using BIN4 = uint32_t;
    using BIN8 = uint64_t;
    const size_t length = name.size();
    uint64_t tail = (length & 0x08U) == 0 ? 0UL : Load<BIN8>(name, length & 0x07U);
    uint64_t head = (length & 0x04U) == 0 ? 0UL : Load<BIN4>(name, length & 0x03U);
    if ((length & 0x02U) != 0) {
        head = (head << 0x10U) | Load<BIN2>(name, length & 0x01U);
    }
    if ((length & 0x01U) != 0) {
        head = (head << 0x08U) | Load<BIN1>(name, length & 0x00U);
    }
    return Slot{(head << 0x08U) | static_cast<uint8_t>(length), tail};
}

template <size_t Count, size_t... Index>
constexpr auto MakeSlots(const std::array<std::string_view, Count>& names, std::index_sequence<Index...>) {
    return std::array<Slot, sizeof...(Index)>{Pack(names[Index])...};
}

constexpr auto Hash(std::string_view name) {
    uint32_t value = 2166136261U;
    for (const auto item : name) {
        value ^= static_cast<unsigned char>(item);
        value *= 16777619U;
    }
    return value;
}

template <size_t Count>
struct ChainTable {
    std::array<uint32_t, std::bit_ceil(Count * 2 < 16 ? 16 : Count * 2)> Heads;
    std::array<uint32_t, Count> Nexts;
};

template <size_t Count>
constexpr ChainTable<Count> MakeChain(const std::array<std::string_view, Count>& names) {
    ChainTable<Count> table{};
    for (auto& head : table.Heads) {
        head = UINT32_MAX;
    }
    for (size_t index = 0; index < Count; index++) {
        const uint32_t bucket = Hash(names[index]) & (table.Heads.size() - 1);
        table.Nexts[index] = table.Heads[bucket];
        table.Heads[bucket] = static_cast<uint32_t>(index);
    }
    return table;
}

template <size_t Count>
constexpr auto HasLongName(const std::array<std::string_view, Count>& names) {
    for (const auto name : names) {
        if (name.size() > PackedItemBytesLimit) {
            return true;
        }
    }
    return false;
}

template <size_t Count>
constexpr auto GetDuplicateIndex(const std::array<std::string_view, Count>& names) {
    for (size_t left = 0; left < Count; left++) {
        for (size_t right = left + 1; right < Count; right++) {
            if (names[left] == names[right]) {
                return left;
            }
        }
    }
    return SIZE_MAX;
}

template <typename Schema, size_t... Index>
constexpr auto MakeNames(std::index_sequence<Index...>) {
    return std::array<std::string_view, sizeof...(Index)>{std::get<Index>(Schema::Members).Name...};
}

template <typename Schema, size_t... Index>
constexpr auto MakeOptionalFlags(std::index_sequence<Index...>) {
    return std::array<bool, sizeof...(Index)>{std::get<Index>(Schema::Members).IsOptional...};
}
}

template <typename Schema>
struct NamedObjectLayout {
    using Members = std::remove_const_t<decltype(Schema::Members)>;
    static constexpr auto Count = std::tuple_size_v<Members>;
    static constexpr auto Names = detail::MakeNames<Schema>(std::make_index_sequence<Count>());
    static constexpr auto Slots = detail::MakeSlots(Names, std::make_index_sequence<Count>());
    static constexpr auto Chain = detail::MakeChain(Names);
    static_assert(detail::GetDuplicateIndex(Names) == SIZE_MAX, "named object member names must be unique");

    static constexpr auto Query(std::string_view name) noexcept {
        if constexpr (Count <= detail::PackedItemCountLimit && !detail::HasLongName(Names)) {
            if (name.size() > detail::PackedItemBytesLimit) {
                return SIZE_MAX;
            }
            const detail::Slot probe = detail::Pack(name);
            for (size_t index = 0; index < Count; index++) {
                if (Slots[index].Head == probe.Head && Slots[index].Tail == probe.Tail) {
                    return index;
                }
            }
            return SIZE_MAX;
        } else {
            const uint32_t hash = detail::Hash(name);
            for (uint32_t cursor = Chain.Heads[hash & (Chain.Heads.size() - 1)]; cursor != UINT32_MAX; cursor = Chain.Nexts[cursor]) {
                if (Names[cursor] == name) {
                    return static_cast<size_t>(cursor);
                }
            }
            return SIZE_MAX;
        }
    }

    static void Parse(std::span<const std::byte> span, std::array<std::span<const std::byte>, Count>& slices) {
        static constexpr auto optionals = detail::MakeOptionalFlags<Schema>(std::make_index_sequence<Count>());
        auto copy = span;
        while (!copy.empty()) {
            auto head = ::binary::DecodeWithLengthPrefix(copy);
            auto tail = ::binary::DecodeWithLengthPrefix(copy);
            const std::string_view name(reinterpret_cast<const char*>(head.data()), head.size());
            const size_t index = Query(name);
            if (index == SIZE_MAX) {
                continue;
            }
            if (slices[index].data() != nullptr) {
                throw std::invalid_argument(std::format("named key '{}' already exists", name));
            }
            slices[index] = tail;
        }

        for (size_t index = 0; index < Count; index++) {
            if (slices[index].data() == nullptr && !optionals[index]) {
                throw std::invalid_argument(std::format("named key '{}' does not exist", Names[index]));
            }
        }
    }
};
}

#endif
