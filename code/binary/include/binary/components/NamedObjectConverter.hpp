#ifndef BINARY_COMPONENTS_NAMEDOBJECTCONVERTER_HPP
#define BINARY_COMPONENTS_NAMEDOBJECTCONVERTER_HPP

#include <array>
#include <memory>
#include <span>
#include <string_view>
#include <tuple>
#include <utility>

#include "binary/Converter.hpp"
#include "binary/ConverterExtensions.hpp"
#include "binary/GeneratorExtensions.hpp"
#include "binary/components/MemberDescriptor.hpp"
#include "binary/components/NamedObjectLayout.hpp"

namespace binary::components {
namespace detail {
template <typename T, typename M, typename Accessor, typename Policy>
class NamedObjectMember {
public:
    static std::shared_ptr<Converter<M>> MakeConverter(const IGenerator& generator, const NamedMember<Accessor, Policy>& descriptor) {
        if constexpr (std::is_void_v<Policy>) {
            return ::binary::GetConverter<M>(generator);
        } else {
            return descriptor.ConverterPolicy.template Get<M>(generator);
        }
    }

    NamedObjectMember(const IGenerator& generator, const NamedMember<Accessor, Policy>& descriptor)
        : converter(MakeConverter(generator, descriptor))
        , Access(descriptor.Access) {
    }

    void Encode(Allocator& allocator, const T& item) const {
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

private:
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
using NamedObjectRuntimeMembers = typename NamedObjectMembersType<T, std::remove_const_t<decltype(Schema::Members)>>::Type;

template <typename T, typename Descriptor>
typename NamedObjectMemberType<T, Descriptor>::Type MakeNamedObjectMember(const IGenerator& generator, const Descriptor& descriptor) {
    return typename NamedObjectMemberType<T, Descriptor>::Type{generator, descriptor};
}

template <typename T, typename Schema>
NamedObjectRuntimeMembers<T, Schema> MakeNamedObjectMembers(const IGenerator& generator) {
    return std::apply(
        [&](const auto&... descriptor) {
            return NamedObjectRuntimeMembers<T, Schema>{MakeNamedObjectMember<T>(generator, descriptor)...};
        },
        Schema::Members
    );
}
}

template <typename T, typename Schema>
class NamedObjectConverter : public Converter<T> {
public:
    explicit NamedObjectConverter(const IGenerator& generator)
        : members(detail::MakeNamedObjectMembers<T, Schema>(generator)) {
    }

    void Encode(Allocator& allocator, const T& item) override {
        EncodeInternal(allocator, item, std::make_index_sequence<Layout::Count>{});
    }

    T Decode(std::span<const std::byte> span) override {
        return DecodeInternal(span, std::make_index_sequence<Layout::Count>{});
    }

private:
    using Layout = NamedObjectLayout<Schema>;
    using RuntimeMembers = detail::NamedObjectRuntimeMembers<T, Schema>;

    template <size_t Index>
    void EncodeInternal(Allocator& allocator, const T& item) const {
        const std::string_view name = Layout::Names[Index];
        ::binary::EncodeWithLengthPrefix(allocator, std::span<const std::byte>(reinterpret_cast<const std::byte*>(name.data()), name.size()));
        std::get<Index>(this->members).Encode(allocator, item);
    }

    template <size_t... Index>
    void EncodeInternal(Allocator& allocator, const T& item, std::index_sequence<Index...>) const {
        (EncodeInternal<Index>(allocator, item), ...);
    }

    template <size_t... Index>
    T DecodeInternal(std::span<const std::byte> span, std::index_sequence<Index...>) {
        std::array<std::span<const std::byte>, sizeof...(Index)> slices{};
        Layout::Parse(span, slices);
        T result{};
        ((std::get<Index>(this->members).Decode(result, slices[Index])), ...);
        return result;
    }

    RuntimeMembers members;
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
