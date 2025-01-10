#pragma once

#ifndef BINARY_COMPONENTS_NAMEDOBJECTDEFINE_HPP
#define BINARY_COMPONENTS_NAMEDOBJECTDEFINE_HPP

#include "binary/components/NamedObjectConverter.hpp"

#define BINARY_NAMED_OBJECT_CONVERTER_BEGIN(ARG_TYPE, ARG_CONVERTER_NAME)                    \
    class ARG_CONVERTER_NAME : public ::binary::components::NamedObjectConverter<ARG_TYPE> { \
    public:                                                                                  \
        ARG_CONVERTER_NAME(::binary::IGenerator& generator)                                  \
            : NamedObjectConverter<ARG_TYPE>(generator, GetContexts()) {}                    \
                                                                                             \
    private:                                                                                 \
        using GenericArgument = ARG_TYPE;                                                    \
                                                                                             \
        static const std::vector<MemberInfo>& GetContexts() {                                \
            static bool initialized = false;                                                 \
            static std::vector<MemberInfo> contexts;                                         \
            if (!initialized) {

#define BINARY_NAMED_OBJECT_CONVERTER_END \
    }                                     \
    initialized = true;                   \
    return contexts;                      \
    }                                     \
    }                                     \
    ;

#define BINARY_NAMED_MEMBER(ARG_NAME)                              \
    BINARY_NAMED_MEMBER_CUSTOM(                                    \
        ARG_NAME, decltype(GenericArgument::ARG_NAME), false,      \
        [](const auto& item) { return item.ARG_NAME; },            \
        [](auto& item, auto&& member) { item.ARG_NAME = member; }, \
        [](auto& generator) { return generator.GetConverter(typeid(decltype(GenericArgument::ARG_NAME))); })

#define BINARY_NAMED_MEMBER_CUSTOM(ARG_NAME, ARG_TYPE, ARG_IS_OPTIONAL, ARG_GET_MEMBER_LAMBDA, ARG_SET_MEMBER_LAMBDA, ARG_GET_CONVERTER_LAMBDA) \
    contexts.push_back(([]() {                                                                                                                  \
        MemberInfo info{};                                                                                                                      \
        info.Name = #ARG_NAME;                                                                                                                  \
        info.IsOptional = ARG_IS_OPTIONAL;                                                                                                      \
        info.EncodeWithLengthPrefix = [](auto& converter, auto& allocator, const auto& item) {                                                  \
            static_cast<::binary::Converter<ARG_TYPE>&>(converter).EncodeWithLengthPrefix(allocator, (ARG_GET_MEMBER_LAMBDA)(item));            \
        };                                                                                                                                      \
        info.Decode = [](auto& item, auto& converter, const auto& span) {                                                                       \
            (ARG_SET_MEMBER_LAMBDA)(item, static_cast<::binary::Converter<ARG_TYPE>&>(converter).Decode(span));                                 \
        };                                                                                                                                      \
        info.GetConverter = [](auto& generator) {                                                                                               \
            return (ARG_GET_CONVERTER_LAMBDA)(generator);                                                                                       \
        };                                                                                                                                      \
        return info;                                                                                                                            \
    })());

#endif
