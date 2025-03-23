#ifndef BINARY_COMPONENTS_TUPLEOBJECT_HPP
#define BINARY_COMPONENTS_TUPLEOBJECT_HPP

#include "binary/GeneratorExtensions.hpp"
#include "binary/components/TupleObjectConverter.hpp"

#define BINARY_TUPLE_OBJECT_CONVERTER(ARG_CONVERTER_NAME, ARG_CONVERTER_TARGET_TYPE)                           \
    class ARG_CONVERTER_NAME : public ::binary::components::TupleObjectConverter<ARG_CONVERTER_TARGET_TYPE> {  \
    public:                                                                                                    \
        ARG_CONVERTER_NAME(const ::binary::IGenerator& generator)                                              \
            : ::binary::components::TupleObjectConverter<ARG_CONVERTER_TARGET_TYPE>(GetContexts(generator)) {} \
                                                                                                               \
    private:                                                                                                   \
        using ConverterTargetType = ARG_CONVERTER_TARGET_TYPE;                                                 \
        using MemberInfo = ::binary::components::TupleObjectConverter<ARG_CONVERTER_TARGET_TYPE>::MemberInfo;  \
        using MemberInfoInitializer = std::function<MemberInfo(const ::binary::IGenerator&, bool)>;            \
                                                                                                               \
        static std::vector<MemberInfo> GetContexts(const ::binary::IGenerator& generator) {                    \
            static bool initialized = false;                                                                   \
            static std::vector<MemberInfoInitializer> initializers;                                            \
            if (initialized == false) {                                                                        \
                initialized = true;                                                                            \
                GetInitializers(initializers);                                                                 \
            }                                                                                                  \
                                                                                                               \
            std::vector<MemberInfo> contexts;                                                                  \
            for (size_t i = 0; i < initializers.size(); i++) {                                                 \
                contexts.emplace_back(initializers.at(i)(generator, i == initializers.size() - 1));            \
            }                                                                                                  \
            return contexts;                                                                                   \
        }                                                                                                      \
                                                                                                               \
        static void GetInitializers(std::vector<MemberInfoInitializer>& initializers) {

#define BINARY_TUPLE_OBJECT_CONVERTER_END() \
    }                                       \
    }                                       \
    ;

#define BINARY_TUPLE_MEMBER(ARG_NAME)      \
    BINARY_TUPLE_MEMBER_CUSTOM(            \
        item.ARG_NAME,                     \
        item.ARG_NAME = std::move(result), \
        ::binary::GetConverter<decltype(ConverterTargetType::ARG_NAME)>(generator))

#define BINARY_TUPLE_MEMBER_CUSTOM(ARG_GET_MEMBER_EXPRESSION, ARG_SET_MEMBER_EXPRESSION, ARG_GET_CONVERTER_EXPRESSION) \
    initializers.push_back([]([[maybe_unused]] auto& generator, bool last) {                                           \
        auto converter = ARG_GET_CONVERTER_EXPRESSION;                                                                 \
        MemberInfo info{};                                                                                             \
        info.Length = converter->Length();                                                                             \
        info.EncodeAuto = [converter](auto& allocator, const auto& item) {                                             \
            converter->EncodeAuto(allocator, ARG_GET_MEMBER_EXPRESSION);                                               \
        };                                                                                                             \
        info.DecodeAuto = [converter](auto& item, auto& span) {                                                        \
            auto result = converter->DecodeAuto(span);                                                                 \
            ARG_SET_MEMBER_EXPRESSION;                                                                                 \
        };                                                                                                             \
        if (last) {                                                                                                    \
            info.Encode = [converter](auto& allocator, const auto& item) {                                             \
                converter->Encode(allocator, ARG_GET_MEMBER_EXPRESSION);                                               \
            };                                                                                                         \
            info.Decode = [converter](auto& item, auto& span) {                                                        \
                auto result = converter->Decode(span);                                                                 \
                ARG_SET_MEMBER_EXPRESSION;                                                                             \
            };                                                                                                         \
        } else {                                                                                                       \
            info.Encode = info.EncodeAuto;                                                                             \
            info.Decode = info.DecodeAuto;                                                                             \
        }                                                                                                              \
        return info;                                                                                                   \
    })

#endif
