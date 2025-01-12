#pragma once

#ifndef BINARY_COMPONENTS_TUPLEOBJECT_HPP
#define BINARY_COMPONENTS_TUPLEOBJECT_HPP

#include "binary/GeneratorExtensions.hpp"
#include "binary/components/TupleObjectConverter.hpp"

#define BINARY_TUPLE_OBJECT_CONVERTER(ARG_TYPE, ARG_CONVERTER_NAME)                          \
    class ARG_CONVERTER_NAME : public ::binary::components::TupleObjectConverter<ARG_TYPE> { \
    public:                                                                                  \
        ARG_CONVERTER_NAME(::binary::IGenerator& generator)                                  \
            : TupleObjectConverter<ARG_TYPE>(GetContexts(generator)) {}                      \
                                                                                             \
    private:                                                                                 \
        using GenericArgument = ARG_TYPE;                                                    \
        using MemberInfoInitializer = std::function<MemberInfo(::binary::IGenerator&)>;      \
                                                                                             \
        static std::vector<MemberInfo> GetContexts(::binary::IGenerator& generator) {        \
            std::vector<MemberInfo> contexts;                                                \
            for (const auto initializer : GetInitializers()) {                               \
                contexts.emplace_back(initializer(generator));                               \
            }                                                                                \
            return contexts;                                                                 \
        }                                                                                    \
                                                                                             \
        static const std::vector<MemberInfoInitializer>& GetInitializers() {                 \
            static bool initialized = false;                                                 \
            static std::vector<MemberInfoInitializer> initializers;                          \
            if (!initialized) {

#define BINARY_TUPLE_OBJECT_CONVERTER_END() \
    }                                       \
    initialized = true;                     \
    return initializers;                    \
    }                                       \
    }                                       \
    ;

#define BINARY_TUPLE_MEMBER(ARG_NAME) \
    BINARY_TUPLE_MEMBER_CUSTOM(       \
        item.ARG_NAME,                \
        item.ARG_NAME = result,       \
        GetConverter<decltype(GenericArgument::ARG_NAME)>(generator))

#define BINARY_TUPLE_MEMBER_CUSTOM(ARG_GET_MEMBER_EXPRESSION, ARG_SET_MEMBER_EXPRESSION, ARG_GET_CONVERTER_EXPRESSION) \
    initializers.push_back(([]() {                                                                                     \
        return []([[maybe_unused]] auto& generator) {                                                                  \
            auto converter = ARG_GET_CONVERTER_EXPRESSION;                                                             \
            MemberInfo info{};                                                                                         \
            info.Length = converter->Length();                                                                         \
            info.Encode = [converter](bool automatic, auto& allocator, const auto& item) {                             \
                if (!automatic) {                                                                                      \
                    converter->Encode(allocator, ARG_GET_MEMBER_EXPRESSION);                                           \
                } else {                                                                                               \
                    converter->EncodeAuto(allocator, ARG_GET_MEMBER_EXPRESSION);                                       \
                }                                                                                                      \
            };                                                                                                         \
            info.Decode = [converter](bool automatic, auto& item, auto& span) {                                        \
                if (!automatic) {                                                                                      \
                    auto result = converter->Decode(span);                                                             \
                    ARG_SET_MEMBER_EXPRESSION;                                                                         \
                } else {                                                                                               \
                    auto result = converter->DecodeAuto(span);                                                         \
                    ARG_SET_MEMBER_EXPRESSION;                                                                         \
                }                                                                                                      \
            };                                                                                                         \
            return info;                                                                                               \
        };                                                                                                             \
    })());

#endif
