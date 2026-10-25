#ifndef BINARY_COMPONENTS_TUPLEOBJECTCONVERTER_HPP
#define BINARY_COMPONENTS_TUPLEOBJECTCONVERTER_HPP

#include <memory>
#include <span>
#include <tuple>
#include <utility>
#include <vector>

#include "binary/Converter.hpp"
#include "binary/GeneratorExtensions.hpp"
#include "binary/components/MemberDescriptor.hpp"
#include "binary/internal/Module.hpp"

namespace binary::components {
namespace detail {
template <typename T, typename M, typename Accessor, typename Policy>
class TupleObjectMember {
private:
    std::shared_ptr<Converter<M>> converter;
    Accessor accessor;

public:
    static std::shared_ptr<Converter<M>> MakeConverter(const IGenerator& generator, const TupleMember<Accessor, Policy>& descriptor) {
        if constexpr (std::is_void_v<Policy>) {
            return ::binary::GetConverter<M>(generator);
        } else {
            return descriptor.ConverterPolicy.template Get<M>(generator);
        }
    }

    TupleObjectMember(const IGenerator& generator, const TupleMember<Accessor, Policy>& descriptor)
        : converter(MakeConverter(generator, descriptor))
        , accessor(descriptor.Accessor) {
    }

    size_t Length() const {
        return this->converter->Length();
    }

    template <bool Last>
    void Encode(Allocator& allocator, const T& item) const {
        if constexpr (std::same_as<Accessor, MemberAccessor<T, M>>) {
            if constexpr (Last) {
                this->converter->Encode(allocator, item.*this->accessor.Member);
            } else {
                this->converter->EncodeAuto(allocator, item.*this->accessor.Member);
            }
        } else {
            if constexpr (Last) {
                this->converter->Encode(allocator, this->accessor.Get(item));
            } else {
                this->converter->EncodeAuto(allocator, this->accessor.Get(item));
            }
        }
    }

    template <bool Last>
    void Decode(T& item, std::span<const std::byte>& span) const {
        if constexpr (std::same_as<Accessor, MemberAccessor<T, M>>) {
            if constexpr (Last) {
                item.*this->accessor.Member = this->converter->Decode(span);
            } else {
                item.*this->accessor.Member = this->converter->DecodeAuto(span);
            }
        } else {
            if constexpr (Last) {
                this->accessor.Set(item, this->converter->Decode(span));
            } else {
                this->accessor.Set(item, this->converter->DecodeAuto(span));
            }
        }
    }
};

template <typename T, typename Descriptor>
struct TupleObjectMemberType;

template <typename T, typename Accessor, typename Policy>
struct TupleObjectMemberType<T, TupleMember<Accessor, Policy>> {
    using Type = TupleObjectMember<T, typename AccessorValue<T, Accessor>::Type, Accessor, Policy>;
};

template <typename T, typename Descriptors>
struct TupleObjectMembersType;

template <typename T, typename... TDescriptor>
struct TupleObjectMembersType<T, std::tuple<TDescriptor...>> {
    using Type = std::tuple<typename TupleObjectMemberType<T, TDescriptor>::Type...>;
};

template <typename T, typename Schema>
using TupleObjectRuntimeMembers = typename TupleObjectMembersType<T, std::remove_const_t<decltype(Schema::Members)>>::Type;

template <typename T, typename Descriptor>
typename TupleObjectMemberType<T, Descriptor>::Type MakeTupleObjectMember(const IGenerator& generator, const Descriptor& descriptor) {
    return typename TupleObjectMemberType<T, Descriptor>::Type{generator, descriptor};
}

template <typename T, typename Schema>
TupleObjectRuntimeMembers<T, Schema> MakeTupleObjectMembers(const IGenerator& generator) {
    return std::apply(
        [&](const auto&... descriptor) {
            return TupleObjectRuntimeMembers<T, Schema>{MakeTupleObjectMember<T>(generator, descriptor)...};
        },
        Schema::Members
    );
}

template <typename T, typename Schema>
size_t GetTupleObjectLength(const IGenerator& generator) {
    auto members = MakeTupleObjectMembers<T, Schema>(generator);
    std::vector<size_t> lengths;
    std::apply([&](const auto&... member) { (lengths.push_back(member.Length()), ...); }, members);
    return ::binary::internal::GetConverterLength(lengths);
}
}

template <typename T, typename Schema>
class TupleObjectConverter : public Converter<T> {
private:
    using Members = detail::TupleObjectRuntimeMembers<T, Schema>;
    static constexpr size_t MemberCount = std::tuple_size_v<Members>;

    template <size_t IsAuto, size_t... Index>
    void EncodeInternal(Allocator& allocator, const T& item, std::index_sequence<Index...>) const {
        (std::get<Index>(this->members).template Encode<(IsAuto == 0 && Index + 1 == MemberCount)>(allocator, item), ...);
    }

    template <size_t IsAuto, size_t... Index>
    void DecodeInternal(T& result, std::span<const std::byte>& span, std::index_sequence<Index...>) const {
        (std::get<Index>(this->members).template Decode<(IsAuto == 0 && Index + 1 == MemberCount)>(result, span), ...);
    }

    Members members;

public:
    explicit TupleObjectConverter(const IGenerator& generator)
        : Converter<T>(detail::GetTupleObjectLength<T, Schema>(generator))
        , members(detail::MakeTupleObjectMembers<T, Schema>(generator)) {
    }

    void Encode(Allocator& allocator, const T& item) override {
        EncodeInternal<0>(allocator, item, std::make_index_sequence<MemberCount>());
    }

    void EncodeAuto(Allocator& allocator, const T& item) override {
        EncodeInternal<1>(allocator, item, std::make_index_sequence<MemberCount>());
    }

    T Decode(std::span<const std::byte> span) override {
        T result{};
        DecodeInternal<0>(result, span, std::make_index_sequence<MemberCount>());
        return result;
    }

    T DecodeAuto(std::span<const std::byte>& span) override {
        T result{};
        DecodeInternal<1>(result, span, std::make_index_sequence<MemberCount>());
        return result;
    }
};
}

namespace binary::internal {
template <typename T, typename Schema>
struct ConverterCreateFunction<::binary::components::TupleObjectConverter<T, Schema>> {
    static auto Invoke(const IGenerator& generator) {
        return std::make_shared<::binary::components::TupleObjectConverter<T, Schema>>(generator);
    }
};
}

#endif
