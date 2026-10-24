#ifndef BINARY_COMPONENTS_MEMBERACCESSOR_HPP
#define BINARY_COMPONENTS_MEMBERACCESSOR_HPP

#include <type_traits>
#include <utility>

namespace binary::components {
template <typename T, typename M>
struct MemberAccessor {
    M T::* Member;

    const M& Get(const T& item) const {
        return item.*Member;
    }

    void Set(T& item, M&& value) const {
        item.*Member = std::move(value);
    }
};

template <typename Getter, typename Setter>
struct CustomAccessor {
    Getter GetMember;
    Setter SetMember;

    decltype(auto) Get(const auto& item) const {
        return this->GetMember(item);
    }

    void Set(auto& item, auto&& value) const {
        this->SetMember(item, std::forward<decltype(value)>(value));
    }
};

template <typename T, typename Accessor>
struct AccessorValue;

template <typename T, typename M>
struct AccessorValue<T, MemberAccessor<T, M>> {
    using Type = M;
};

template <typename T, typename Getter, typename Setter>
struct AccessorValue<T, CustomAccessor<Getter, Setter>> {
    using Type = std::remove_cvref_t<std::invoke_result_t<Getter, const T&>>;
};
}

#endif
