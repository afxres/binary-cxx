#ifndef BINARY_COMPONENTS_MEMBERDESCRIPTOR_HPP
#define BINARY_COMPONENTS_MEMBERDESCRIPTOR_HPP

#include <concepts>
#include <memory>
#include <string_view>
#include <type_traits>

#include "binary/Converter.hpp"
#include "binary/IGenerator.hpp"
#include "binary/components/MemberAccessor.hpp"

namespace binary::components {
struct EmptyConverterPolicy {};

template <typename TConverter>
struct FixedConverterPolicy {
    template <typename M>
    std::shared_ptr<Converter<M>> Get(const IGenerator&) const {
        return std::make_shared<TConverter>();
    }
};

template <typename Accessor, typename Policy = void>
class NamedMember {
private:
    using PolicyValue = std::conditional_t<std::is_void_v<Policy>, EmptyConverterPolicy, Policy>;

public:
    std::string_view Name;
    bool IsOptional = false;
    Accessor Access;
    [[no_unique_address]] PolicyValue ConverterPolicy{};

    template <typename T, typename M>
    constexpr NamedMember(std::string_view name, M T::* member, bool optional = false)
        requires std::same_as<Accessor, MemberAccessor<T, M>>
        : Name(name)
        , IsOptional(optional)
        , Access{member} {
    }

    template <typename Getter, typename Setter>
    constexpr NamedMember(std::string_view name, Getter getter, Setter setter, bool optional = false)
        requires std::same_as<Accessor, CustomAccessor<Getter, Setter>>
        : Name(name)
        , IsOptional(optional)
        , Access{getter, setter} {
    }

    template <typename Getter, typename Setter, typename ActualPolicy>
    constexpr NamedMember(std::string_view name, Getter getter, Setter setter, ActualPolicy policy, bool optional = false)
        requires std::same_as<Accessor, CustomAccessor<Getter, Setter>> && std::same_as<Policy, ActualPolicy> && (!std::same_as<ActualPolicy, bool>)
        : Name(name)
        , IsOptional(optional)
        , Access{getter, setter}
        , ConverterPolicy(std::move(policy)) {
    }
};

template <typename T, typename M>
NamedMember(std::string_view, M T::*, bool = false) -> NamedMember<MemberAccessor<T, M>>;

template <typename Getter, typename Setter>
NamedMember(std::string_view, Getter, Setter, bool = false) -> NamedMember<CustomAccessor<Getter, Setter>>;

template <typename Getter, typename Setter, typename Policy>
    requires(!std::same_as<Policy, bool>)
NamedMember(std::string_view, Getter, Setter, Policy) -> NamedMember<CustomAccessor<Getter, Setter>, Policy>;

template <typename Accessor, typename Policy = void>
class TupleMember {
private:
    using PolicyValue = std::conditional_t<std::is_void_v<Policy>, EmptyConverterPolicy, Policy>;

public:
    Accessor Access;
    [[no_unique_address]] PolicyValue ConverterPolicy{};

    template <typename T, typename M>
    constexpr TupleMember(M T::* member)
        requires std::same_as<Accessor, MemberAccessor<T, M>>
        : Access{member} {
    }

    template <typename Getter, typename Setter>
    constexpr TupleMember(Getter getter, Setter setter)
        requires std::same_as<Accessor, CustomAccessor<Getter, Setter>>
        : Access{getter, setter} {
    }

    template <typename Getter, typename Setter, typename ActualPolicy>
    constexpr TupleMember(Getter getter, Setter setter, ActualPolicy policy)
        requires std::same_as<Accessor, CustomAccessor<Getter, Setter>> && std::same_as<Policy, ActualPolicy> && (!std::same_as<ActualPolicy, bool>)
        : Access{getter, setter}
        , ConverterPolicy(std::move(policy)) {
    }
};

template <typename T, typename M>
TupleMember(M T::*) -> TupleMember<MemberAccessor<T, M>>;

template <typename Getter, typename Setter>
TupleMember(Getter, Setter) -> TupleMember<CustomAccessor<Getter, Setter>>;

template <typename Getter, typename Setter, typename Policy>
    requires(!std::same_as<Policy, bool>)
TupleMember(Getter, Setter, Policy) -> TupleMember<CustomAccessor<Getter, Setter>, Policy>;
}

#endif
