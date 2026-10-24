#ifndef BINARY_COMPONENTS_NAMEDOBJECTCONVERTER_HPP
#define BINARY_COMPONENTS_NAMEDOBJECTCONVERTER_HPP

#include <array>
#include <cassert>
#include <memory>
#include <span>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

#include "binary/Converter.hpp"
#include "binary/ConverterExtensions.hpp"
#include "binary/GeneratorExtensions.hpp"
#include "binary/components/MemberDescriptor.hpp"
#include "binary/components/NamedObjectDecoder.hpp"

namespace binary::components {
template <typename T, typename M, typename Accessor, typename Policy>
class NamedObjectMember {
public:
    static std::vector<std::byte> MakeHeader(const IGenerator& generator, std::string_view name) {
        return Allocator::Invoke([&](Allocator& allocator) {
            ::binary::GetConverter<std::string>(generator)->Encode(allocator, std::string(name));
        });
    }

    static std::shared_ptr<Converter<M>> MakeConverter(const IGenerator& generator, const NamedMember<Accessor, Policy>& descriptor) {
        if constexpr (std::is_void_v<Policy>) {
            return ::binary::GetConverter<M>(generator);
        } else {
            return descriptor.ConverterPolicy.template Get<M>(generator);
        }
    }

    NamedObjectMember(const IGenerator& generator, const NamedMember<Accessor, Policy>& descriptor)
        : Name(descriptor.Name)
        , IsOptional(descriptor.IsOptional)
        , Header(MakeHeader(generator, descriptor.Name))
        , converter(MakeConverter(generator, descriptor))
        , Access(descriptor.Access) {
    }

    void Encode(Allocator& allocator, const T& item) const {
        ::binary::EncodeWithLengthPrefix(allocator, this->Header);
        if constexpr (std::same_as<Accessor, MemberAccessor<T, M>>) {
            this->converter->EncodeWithLengthPrefix(allocator, item.*this->Access.Member);
        } else {
            this->converter->EncodeWithLengthPrefix(allocator, this->Access.Get(item));
        }
    }

    void Decode(T& item, std::span<const std::byte> span) const {
        if (span.data() != nullptr) {
            if constexpr (std::same_as<Accessor, MemberAccessor<T, M>>) {
                item.*this->Access.Member = this->converter->Decode(span);
            } else {
                this->Access.Set(item, this->converter->Decode(span));
            }
        }
    }

    std::string Name;
    bool IsOptional;
    std::vector<std::byte> Header;
    std::shared_ptr<Converter<M>> converter;
    Accessor Access;
};

template <typename T, typename Descriptor>
struct NamedObjectMemberType;

template <typename T, typename Accessor, typename Policy>
struct NamedObjectMemberType<T, NamedMember<Accessor, Policy>> {
    using Type = NamedObjectMember<T, typename AccessorValue<T, Accessor>::Type, Accessor, Policy>;
};

template <typename T, typename Descriptors>
struct NamedObjectMembersType;

template <typename T, typename... TDescriptor>
struct NamedObjectMembersType<T, std::tuple<TDescriptor...>> {
    using Type = std::tuple<typename NamedObjectMemberType<T, TDescriptor>::Type...>;
};

template <typename T, typename Schema>
class NamedObjectConverter : public Converter<T> {
private:
    using RuntimeMembers = typename NamedObjectMembersType<T, std::remove_const_t<decltype(Schema::Members)>>::Type;

    template <typename Descriptor>
    static typename NamedObjectMemberType<T, Descriptor>::Type MakeMember(const IGenerator& generator, const Descriptor& descriptor) {
        return typename NamedObjectMemberType<T, Descriptor>::Type{generator, descriptor};
    }

    static RuntimeMembers MakeMembers(const IGenerator& generator) {
        return std::apply(
            [&](const auto&... descriptor) {
                return RuntimeMembers{MakeMember(generator, descriptor)...};
            },
            Schema::Members
        );
    }

    static std::unique_ptr<NamedObjectDecoder> MakeDecoder(const RuntimeMembers& members) {
        std::vector<std::vector<std::byte>> headers;
        std::vector<std::string> names;
        std::vector<uint8_t> optional;
        std::apply(
            [&](const auto&... member) {
                (headers.push_back(member.Header), ...);
                (names.push_back(member.Name), ...);
                (optional.push_back(member.IsOptional ? 1 : 0), ...);
            },
            members
        );
        return std::make_unique<NamedObjectDecoder>(headers, names, optional);
    }

public:
    explicit NamedObjectConverter(const IGenerator& generator)
        : members(MakeMembers(generator))
        , decoder(MakeDecoder(this->members)) {
    }

    void Encode(Allocator& allocator, const T& item) override {
        std::apply(
            [&](const auto&... member) {
                (member.Encode(allocator, item), ...);
            },
            this->members
        );
    }

    T Decode(std::span<const std::byte> span) override {
        constexpr size_t count = std::tuple_size_v<RuntimeMembers>;
        return DecodeInternal(span, std::make_index_sequence<count>{});
    }

private:
    template <size_t... I>
    T DecodeInternal(std::span<const std::byte> span, std::index_sequence<I...>) {
        std::array<std::span<const std::byte>, sizeof...(I)> slices{};
        this->decoder->Invoke(span, slices);
        T result{};
        ((std::get<I>(this->members).Decode(result, slices[I])), ...);
        return result;
    }

    RuntimeMembers members;
    std::unique_ptr<NamedObjectDecoder> decoder;
};
}

namespace binary::internal {
template <typename T, typename Schema>
struct ConverterCreateFunction<::binary::components::NamedObjectConverter<T, Schema>> {
    static auto Invoke(const IGenerator& generator) {
        return std::make_shared<::binary::components::NamedObjectConverter<T, Schema>>(generator);
    }
};
}

#endif
