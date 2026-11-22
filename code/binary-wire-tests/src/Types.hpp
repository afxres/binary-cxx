#ifndef WIRE_TYPES_HPP
#define WIRE_TYPES_HPP

#include <cstdint>
#include <optional>
#include <string>
#include <tuple>

#include <binary/components/MemberDescriptor.hpp>

namespace tests::binary::wire {
struct Tiny {
    std::uint8_t X{};

    bool operator==(const Tiny&) const = default;
};

struct Person {
    std::int32_t Id{};
    std::string Name;

    bool operator==(const Person&) const = default;
};

struct Mid {
    std::int32_t A{};
    std::int32_t B{};
    std::int32_t C{};

    bool operator==(const Mid&) const = default;
};

struct WithOpt {
    std::optional<std::int32_t> V;

    bool operator==(const WithOpt&) const = default;
};

struct TupleTwoInt {
    std::int32_t A{};
    std::int32_t B{};

    bool operator==(const TupleTwoInt&) const = default;
};

struct TupleIntStr {
    std::int32_t A{};
    std::string B;

    bool operator==(const TupleIntStr&) const = default;
};

enum class Color : std::int32_t {
    Red = 1,
    Green = 2,
};

struct TinySchema {
    static constexpr auto Members = std::tuple{
        ::binary::components::NamedMember{"x", &Tiny::X},
    };
};

struct PersonSchema {
    static constexpr auto Members = std::tuple{
        ::binary::components::NamedMember{"id", &Person::Id},
        ::binary::components::NamedMember{"name", &Person::Name},
    };
};

struct MidSchema {
    static constexpr auto Members = std::tuple{
        ::binary::components::NamedMember{"a", &Mid::A},
        ::binary::components::NamedMember{"b", &Mid::B},
        ::binary::components::NamedMember{"c", &Mid::C},
    };
};

struct WithOptSchema {
    static constexpr auto Members = std::tuple{
        ::binary::components::NamedMember{"v", &WithOpt::V},
    };
};

struct TupleTwoIntSchema {
    static constexpr auto Members = std::tuple{
        ::binary::components::TupleMember{&TupleTwoInt::A},
        ::binary::components::TupleMember{&TupleTwoInt::B},
    };
};

struct TupleIntStrSchema {
    static constexpr auto Members = std::tuple{
        ::binary::components::TupleMember{&TupleIntStr::A},
        ::binary::components::TupleMember{&TupleIntStr::B},
    };
};

inline TinySchema GetNamedObjectSchema(Tiny*) {
    return {};
}

inline PersonSchema GetNamedObjectSchema(Person*) {
    return {};
}

inline MidSchema GetNamedObjectSchema(Mid*) {
    return {};
}

inline WithOptSchema GetNamedObjectSchema(WithOpt*) {
    return {};
}

inline TupleTwoIntSchema GetTupleObjectSchema(TupleTwoInt*) {
    return {};
}

inline TupleIntStrSchema GetTupleObjectSchema(TupleIntStr*) {
    return {};
}
}

#endif
