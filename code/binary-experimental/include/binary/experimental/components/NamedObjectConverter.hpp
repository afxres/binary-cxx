#ifndef BINARY_EXPERIMENTAL_COMPONENTS_NAMEDOBJECTCONVERTER_HPP
#define BINARY_EXPERIMENTAL_COMPONENTS_NAMEDOBJECTCONVERTER_HPP

#include <array>
#include <cstddef>
#include <cstdint>
#include <format>
#include <span>
#include <stdexcept>
#include <string_view>
#include <tuple>
#include <utility>

#include "binary/ConverterExtensions.hpp"
#include "binary/components/MemberDescriptor.hpp"
#include "binary/experimental/helpers/ConverterDecodeWithLengthPrefixMethodHelper.hpp"
#include "binary/experimental/helpers/ConverterEncodeWithLengthPrefixMethodHelper.hpp"
#include "binary/experimental/helpers/GetConverterHelper.hpp"
#include "binary/experimental/internal/Define.hpp"

namespace binary::experimental::components {
template <typename T, typename Schema>
struct NamedObjectConverter {
    using Members = std::remove_const_t<decltype(Schema::Members)>;
    static constexpr size_t MemberCount = std::tuple_size_v<Members>;

    template <size_t Index>
    using DescriptorType = std::tuple_element_t<Index, Members>;

    template <size_t Index>
    using AccessorType = std::remove_cvref_t<decltype(std::declval<DescriptorType<Index>&>().Access)>;

    template <size_t Index>
    using MemberType = std::remove_cv_t<typename ::binary::components::AccessorValue<T, AccessorType<Index>>::Type>;

    template <size_t Index>
    using ElementConverterType = typename ::binary::experimental::helpers::GetConverterHelper<MemberType<Index>>::Type;

    template <size_t... Index>
    static constexpr auto MakeNameTable(std::index_sequence<Index...>) {
        return std::array<std::string_view, sizeof...(Index)>{std::get<Index>(Schema::Members).Name...};
    }

    template <size_t... Index>
    static constexpr auto MakeOptionalTable(std::index_sequence<Index...>) {
        return std::array<bool, sizeof...(Index)>{std::get<Index>(Schema::Members).IsOptional...};
    }

    static constexpr size_t FindMember(const std::array<std::string_view, MemberCount>& names, std::string_view name) {
        for (size_t index = 0; index < MemberCount; index++) {
            if (names[index] == name) {
                return index;
            }
        }
        return SIZE_MAX;
    }

    template <size_t Index>
    static void EncodeMember(Allocator& allocator, const T& item) {
        const auto& descriptor = std::get<Index>(Schema::Members);
        const std::string_view name = descriptor.Name;
        ::binary::EncodeWithLengthPrefix(allocator, std::span<const std::byte>(reinterpret_cast<const std::byte*>(name.data()), name.size()));
        ::binary::experimental::helpers::ConverterEncodeWithLengthPrefixMethodHelper<ElementConverterType<Index>>::Invoke(allocator, descriptor.Access.Get(item));
    }

    template <size_t... Index>
    static void EncodeMembers(Allocator& allocator, const T& item, std::index_sequence<Index...>) {
        (EncodeMember<Index>(allocator, item), ...);
    }

    template <size_t Index>
    static void DecodeMember(T& item, std::span<const std::byte> span) {
        auto value = ElementConverterType<Index>::Decode(span);
        std::get<Index>(Schema::Members).Access.Set(item, std::move(value));
    }

    template <size_t... Index>
    static void DecodeMembers(T& item, const std::array<std::span<const std::byte>, MemberCount>& slices, std::index_sequence<Index...>) {
        ((slices[Index].data() != nullptr ? (DecodeMember<Index>(item, slices[Index]), void()) : void()), ...);
    }

    BINARY_EXPERIMENTAL_DEFINE_STATIC_LENGTH_METHOD() {
        return 0;
    }

    BINARY_EXPERIMENTAL_DEFINE_STATIC_ENCODE_METHOD(T) {
        EncodeMembers(allocator, item, std::make_index_sequence<MemberCount>());
    }

    BINARY_EXPERIMENTAL_DEFINE_STATIC_DECODE_METHOD(T) {
        static constexpr auto names = MakeNameTable(std::make_index_sequence<MemberCount>());
        static constexpr auto optionals = MakeOptionalTable(std::make_index_sequence<MemberCount>());
        std::array<std::span<const std::byte>, MemberCount> slices{};
        auto copy = span;
        while (!copy.empty()) {
            auto head = ::binary::DecodeWithLengthPrefix(copy);
            auto tail = ::binary::DecodeWithLengthPrefix(copy);
            const std::string_view name(reinterpret_cast<const char*>(head.data()), head.size());
            const auto index = FindMember(names, name);
            if (index == SIZE_MAX) {
                continue;
            }
            if (slices[index].data() != nullptr) {
                throw std::invalid_argument(std::format("named key '{}' already exists", name));
            }
            slices[index] = tail;
        }

        for (size_t index = 0; index < MemberCount; index++) {
            if (slices[index].data() == nullptr && !optionals[index]) {
                throw std::invalid_argument(std::format("named key '{}' does not exist", names[index]));
            }
        }

        T result{};
        DecodeMembers(result, slices, std::make_index_sequence<MemberCount>());
        return result;
    }
};
}

namespace binary::experimental::helpers {
template <typename T>
    requires requires { GetNamedObjectSchema(static_cast<std::remove_cv_t<T>*>(nullptr)); }
struct GetConverterHelper<T> {
    using Type = ::binary::experimental::components::NamedObjectConverter<T, std::remove_cvref_t<decltype(GetNamedObjectSchema(static_cast<std::remove_cv_t<T>*>(nullptr)))>>;
};
}

#endif
