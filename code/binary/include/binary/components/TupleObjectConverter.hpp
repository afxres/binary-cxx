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
template <typename T, typename M, typename Accessor, typename Policy>
class TupleObjectMember {
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
        , Access(descriptor.Access) {
        this->Length = this->converter->Length();
    }

    template <bool Last>
    void Encode(Allocator& allocator, const T& item) const {
        if constexpr (std::same_as<Accessor, MemberAccessor<T, M>>) {
            if constexpr (Last) {
                this->converter->Encode(allocator, item.*this->Access.Member);
            } else {
                this->converter->EncodeAuto(allocator, item.*this->Access.Member);
            }
        } else {
            if constexpr (Last) {
                this->converter->Encode(allocator, this->Access.Get(item));
            } else {
                this->converter->EncodeAuto(allocator, this->Access.Get(item));
            }
        }
    }

    void EncodeAuto(Allocator& allocator, const T& item) const {
        if constexpr (std::same_as<Accessor, MemberAccessor<T, M>>) {
            this->converter->EncodeAuto(allocator, item.*this->Access.Member);
        } else {
            this->converter->EncodeAuto(allocator, this->Access.Get(item));
        }
    }

    template <bool Last>
    void Decode(T& item, std::span<const std::byte>& span) const {
        if constexpr (std::same_as<Accessor, MemberAccessor<T, M>>) {
            if constexpr (Last) {
                item.*this->Access.Member = this->converter->Decode(span);
            } else {
                item.*this->Access.Member = this->converter->DecodeAuto(span);
            }
        } else {
            if constexpr (Last) {
                this->Access.Set(item, this->converter->Decode(span));
            } else {
                this->Access.Set(item, this->converter->DecodeAuto(span));
            }
        }
    }

    void DecodeAuto(T& item, std::span<const std::byte>& span) const {
        if constexpr (std::same_as<Accessor, MemberAccessor<T, M>>) {
            item.*this->Access.Member = this->converter->DecodeAuto(span);
        } else {
            this->Access.Set(item, this->converter->DecodeAuto(span));
        }
    }

    size_t Length;
    std::shared_ptr<Converter<M>> converter;
    Accessor Access;
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
class TupleObjectConverter : public Converter<T> {
private:
    using RuntimeMembers = typename TupleObjectMembersType<T, std::remove_const_t<decltype(Schema::Members)>>::Type;

    template <typename Descriptor>
    static typename TupleObjectMemberType<T, Descriptor>::Type MakeMember(const IGenerator& generator, const Descriptor& descriptor) {
        return typename TupleObjectMemberType<T, Descriptor>::Type{generator, descriptor};
    }

    static RuntimeMembers MakeMembers(const IGenerator& generator) {
        return std::apply(
            [&](const auto&... descriptor) {
                return RuntimeMembers{MakeMember(generator, descriptor)...};
            },
            Schema::Members
        );
    }

    static size_t ComputeLength(const IGenerator& generator) {
        auto members = MakeMembers(generator);
        std::vector<size_t> lengths;
        std::apply(
            [&](const auto&... member) {
                (lengths.push_back(member.Length), ...);
            },
            members
        );
        return ::binary::internal::GetConverterLength(lengths);
    }

public:
    explicit TupleObjectConverter(const IGenerator& generator)
        : Converter<T>(ComputeLength(generator))
        , members(MakeMembers(generator)) {
    }

    void Encode(Allocator& allocator, const T& item) override {
        EncodeInternal(allocator, item, std::make_index_sequence<std::tuple_size_v<RuntimeMembers>>{});
    }

    void EncodeAuto(Allocator& allocator, const T& item) override {
        std::apply(
            [&](const auto&... member) {
                (member.EncodeAuto(allocator, item), ...);
            },
            this->members
        );
    }

    T Decode(std::span<const std::byte> span) override {
        T result{};
        DecodeInternal(result, span, std::make_index_sequence<std::tuple_size_v<RuntimeMembers>>{});
        return result;
    }

    T DecodeAuto(std::span<const std::byte>& span) override {
        T result{};
        std::apply(
            [&](const auto&... member) {
                (member.DecodeAuto(result, span), ...);
            },
            this->members
        );
        return result;
    }

private:
    template <size_t... I>
    void EncodeInternal(Allocator& allocator, const T& item, std::index_sequence<I...>) const {
        constexpr size_t count = sizeof...(I);
        ((std::get<I>(this->members).template Encode<(I + 1 == count)>(allocator, item)), ...);
    }

    template <size_t... I>
    void DecodeInternal(T& result, std::span<const std::byte>& span, std::index_sequence<I...>) const {
        constexpr size_t count = sizeof...(I);
        ((std::get<I>(this->members).template Decode<(I + 1 == count)>(result, span)), ...);
    }

    RuntimeMembers members;
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
