#ifndef BINARY_EXPERIMENTAL_COMPONENTS_NAMEDOBJECTCONVERTER_HPP
#define BINARY_EXPERIMENTAL_COMPONENTS_NAMEDOBJECTCONVERTER_HPP

#include <array>
#include <cstddef>
#include <span>
#include <string_view>
#include <tuple>
#include <type_traits>
#include <utility>

#include "binary/ConverterExtensions.hpp"
#include "binary/components/MemberAccessor.hpp"
#include "binary/components/NamedObjectLayout.hpp"
#include "binary/experimental/helpers/ConverterEncodeWithLengthPrefixMethodHelper.hpp"
#include "binary/experimental/helpers/GetConverterHelper.hpp"
#include "binary/experimental/internal/Define.hpp"

namespace binary::experimental::components {
namespace detail {
template <size_t Index, typename T, typename Schema>
struct NamedObjectMember {
    using Members = std::remove_const_t<decltype(Schema::Members)>;
    using DescriptorType = std::tuple_element_t<Index, Members>;
    using AccessorType = std::remove_cvref_t<decltype(std::declval<DescriptorType&>().Accessor)>;
    using MemberType = std::remove_cv_t<typename ::binary::components::AccessorValue<T, AccessorType>::Type>;
    using ElementConverterType = typename ::binary::experimental::helpers::GetConverterHelper<MemberType>::Type;

    static void Encode(Allocator& allocator, const T& item) {
        const auto& descriptor = std::get<Index>(Schema::Members);
        const std::string_view name = ::binary::components::NamedObjectLayout<Schema>::Names[Index];
        ::binary::EncodeWithLengthPrefix(allocator, std::span<const std::byte>(reinterpret_cast<const std::byte*>(name.data()), name.size()));
        ::binary::experimental::helpers::ConverterEncodeWithLengthPrefixMethodHelper<ElementConverterType>::Invoke(allocator, descriptor.Accessor.Get(item));
    }

    static void Decode(T& item, std::span<const std::byte> span) {
        auto value = ElementConverterType::Decode(span);
        std::get<Index>(Schema::Members).Accessor.Set(item, std::move(value));
    }
};
}

template <typename T, typename Schema>
class NamedObjectConverter {
private:
    using Layout = ::binary::components::NamedObjectLayout<Schema>;

    template <size_t... Index>
    static void EncodeInternal(Allocator& allocator, const T& item, std::index_sequence<Index...>) {
        (detail::NamedObjectMember<Index, T, Schema>::Encode(allocator, item), ...);
    }

    template <size_t... Index>
    static T DecodeInternal(std::span<const std::byte> span, std::index_sequence<Index...>) {
        std::array<std::span<const std::byte>, sizeof...(Index)> slices{};
        Layout::Parse(span, slices);
        T result{};
        ((slices[Index].data() != nullptr ? (detail::NamedObjectMember<Index, T, Schema>::Decode(result, slices[Index]), void()) : void()), ...);
        return result;
    }

public:
    BINARY_EXPERIMENTAL_DEFINE_STATIC_LENGTH_METHOD() {
        return 0;
    }

    BINARY_EXPERIMENTAL_DEFINE_STATIC_ENCODE_METHOD(T) {
        EncodeInternal(allocator, item, std::make_index_sequence<Layout::Count>());
    }

    BINARY_EXPERIMENTAL_DEFINE_STATIC_DECODE_METHOD(T) {
        return DecodeInternal(span, std::make_index_sequence<Layout::Count>());
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
