#pragma once

#ifndef BINARY_COMPONENTS_TUPLEOBJECT_HPP
#define BINARY_COMPONENTS_TUPLEOBJECT_HPP

#include "binary/components/TupleObjectConverter.hpp"

#define BINARY_TUPLE_OBJECT_CONVERTER_BEGIN(ARG_TYPE, ARG_CONVERTER_NAME)                    \
    class ARG_CONVERTER_NAME : public ::binary::components::TupleObjectConverter<ARG_TYPE> { \
    public:                                                                                  \
        ARG_CONVERTER_NAME(::binary::IGenerator& generator)                                  \
            : TupleObjectConverter<ARG_TYPE>(generator, GetContexts()) {}                    \
                                                                                             \
    private:                                                                                 \
        using GenericArgument = ARG_TYPE;                                                    \
                                                                                             \
        static const std::vector<MemberInfo>& GetContexts() {                                \
            static bool initialized = false;                                                 \
            static std::vector<MemberInfo> contexts;                                         \
            if (!initialized) {

#define BINARY_TUPLE_OBJECT_CONVERTER_END() \
    }                                       \
    initialized = true;                     \
    return contexts;                        \
    }                                       \
    }                                       \
    ;

#define BINARY_TUPLE_MEMBER(ARG_NAME)                              \
    BINARY_TUPLE_MEMBER_CUSTOM(                                    \
        decltype(GenericArgument::ARG_NAME),                       \
        [](const auto& item) { return item.ARG_NAME; },            \
        [](auto& item, auto&& member) { item.ARG_NAME = member; }, \
        [](auto& generator) { return generator.GetConverter(typeid(decltype(GenericArgument::ARG_NAME))); })

#define BINARY_TUPLE_MEMBER_CUSTOM(ARG_TYPE, ARG_GET_MEMBER_LAMBDA, ARG_SET_MEMBER_LAMBDA, ARG_GET_CONVERTER_LAMBDA) \
    contexts.push_back(([]() {                                                                                       \
        MemberInfo info{};                                                                                           \
        info.Encode = [](bool automatic, auto& converter, auto& allocator, const auto& item) {                       \
            auto& reference = static_cast<::binary::Converter<ARG_TYPE>&>(converter);                                \
            if (!automatic) {                                                                                        \
                reference.Encode(allocator, (ARG_GET_MEMBER_LAMBDA)(item));                                          \
            } else {                                                                                                 \
                reference.EncodeAuto(allocator, (ARG_GET_MEMBER_LAMBDA)(item));                                      \
            }                                                                                                        \
        };                                                                                                           \
        info.Decode = [](bool automatic, auto& item, auto& converter, auto& span) {                                  \
            auto& reference = static_cast<::binary::Converter<ARG_TYPE>&>(converter);                                \
            if (!automatic) {                                                                                        \
                (ARG_SET_MEMBER_LAMBDA)(item, reference.Decode(span));                                               \
            } else {                                                                                                 \
                (ARG_SET_MEMBER_LAMBDA)(item, reference.DecodeAuto(span));                                           \
            }                                                                                                        \
        };                                                                                                           \
        info.GetConverter = [](auto& generator) {                                                                    \
            return (ARG_GET_CONVERTER_LAMBDA)(generator);                                                            \
        };                                                                                                           \
        return info;                                                                                                 \
    })());

#endif
