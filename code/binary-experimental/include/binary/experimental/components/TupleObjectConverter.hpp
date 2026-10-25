#ifndef BINARY_EXPERIMENTAL_COMPONENTS_TUPLEOBJECTCONVERTER_HPP
#define BINARY_EXPERIMENTAL_COMPONENTS_TUPLEOBJECTCONVERTER_HPP

#include <cstddef>
#include <span>
#include <tuple>
#include <type_traits>
#include <utility>

#include "binary/ConverterExtensions.hpp"
#include "binary/components/MemberAccessor.hpp"
#include "binary/experimental/helpers/ConverterDecodeAutoMethodHelper.hpp"
#include "binary/experimental/helpers/ConverterEncodeAutoMethodHelper.hpp"
#include "binary/experimental/helpers/GetConverterHelper.hpp"
#include "binary/experimental/internal/Define.hpp"
#include "binary/internal/Module.hpp"

namespace binary::experimental::components {
namespace detail {
template <typename T, typename Schema, size_t Index>
struct TupleObjectMember {
    using Members = std::remove_const_t<decltype(Schema::Members)>;
    using DescriptorType = std::tuple_element_t<Index, Members>;
    using AccessorType = std::remove_cvref_t<decltype(std::declval<DescriptorType&>().Accessor)>;
    using MemberType = std::remove_cv_t<typename ::binary::components::AccessorValue<T, AccessorType>::Type>;
    using ElementConverterType = typename ::binary::experimental::helpers::GetConverterHelper<MemberType>::Type;

    static constexpr auto Length() {
        return ElementConverterType::Length();
    }

    template <bool Last>
    static void Encode(Allocator& allocator, const T& item) {
        const auto& descriptor = std::get<Index>(Schema::Members);
        if constexpr (Last) {
            ElementConverterType::Encode(allocator, descriptor.Accessor.Get(item));
        } else {
            ::binary::experimental::helpers::ConverterEncodeAutoMethodHelper<ElementConverterType>::Invoke(allocator, descriptor.Accessor.Get(item));
        }
    }

    template <bool Last>
    static void Decode(T& item, std::span<const std::byte>& span) {
        if constexpr (Last) {
            std::get<Index>(Schema::Members).Accessor.Set(item, ElementConverterType::Decode(span));
        } else {
            std::get<Index>(Schema::Members).Accessor.Set(item, ::binary::experimental::helpers::ConverterDecodeAutoMethodHelper<ElementConverterType>::Invoke(span));
        }
    }
};

template <typename T, typename Schema, size_t... Index>
constexpr size_t GetTupleObjectLength(std::index_sequence<Index...>) {
    return ::binary::internal::GetConverterLength(std::array<size_t, sizeof...(Index)>{detail::TupleObjectMember<T, Schema, Index>::Length()...});
}
}

template <typename T, typename Schema>
class TupleObjectConverter {
private:
    using Members = std::remove_const_t<decltype(Schema::Members)>;
    static constexpr size_t MemberCount = std::tuple_size_v<Members>;

    template <size_t IsAuto, size_t... Index>
    static void EncodeInternal(Allocator& allocator, const T& item, std::index_sequence<Index...>) {
        (detail::TupleObjectMember<T, Schema, Index>::template Encode<(IsAuto == 0 && Index + 1 == MemberCount)>(allocator, item), ...);
    }

    template <size_t IsAuto, size_t... Index>
    static void DecodeInternal(T& result, std::span<const std::byte>& span, std::index_sequence<Index...>) {
        (detail::TupleObjectMember<T, Schema, Index>::template Decode<(IsAuto == 0 && Index + 1 == MemberCount)>(result, span), ...);
    }

public:
    BINARY_EXPERIMENTAL_DEFINE_STATIC_LENGTH_METHOD() {
        return detail::GetTupleObjectLength<T, Schema>(std::make_index_sequence<MemberCount>());
    }

    BINARY_EXPERIMENTAL_DEFINE_STATIC_ENCODE_METHOD(T) {
        EncodeInternal<0>(allocator, item, std::make_index_sequence<MemberCount>());
    }

    BINARY_EXPERIMENTAL_DEFINE_STATIC_ENCODE_AUTO_METHOD(T) {
        EncodeInternal<1>(allocator, item, std::make_index_sequence<MemberCount>());
    }

    BINARY_EXPERIMENTAL_DEFINE_STATIC_DECODE_METHOD(T) {
        std::span<const std::byte> copy = span;
        T result{};
        DecodeInternal<0>(result, copy, std::make_index_sequence<MemberCount>());
        return result;
    }

    BINARY_EXPERIMENTAL_DEFINE_STATIC_DECODE_AUTO_METHOD(T) {
        T result{};
        DecodeInternal<1>(result, span, std::make_index_sequence<MemberCount>());
        return result;
    }
};
}

namespace binary::experimental::helpers {
template <typename T>
    requires requires { GetTupleObjectSchema(static_cast<std::remove_cv_t<T>*>(nullptr)); }
struct GetConverterHelper<T> {
    using Type = ::binary::experimental::components::TupleObjectConverter<T, std::remove_cvref_t<decltype(GetTupleObjectSchema(static_cast<std::remove_cv_t<T>*>(nullptr)))>>;
};
}

#endif
