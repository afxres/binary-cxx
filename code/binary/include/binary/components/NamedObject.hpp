#ifndef BINARY_COMPONENTS_NAMEDOBJECT_HPP
#define BINARY_COMPONENTS_NAMEDOBJECT_HPP

#include "binary/GeneratorExtensions.hpp"
#include "binary/components/NamedObjectConverter.hpp"

#define BINARY_NAMED_OBJECT_CONVERTER(ARG_CONVERTER_NAME, ARG_CONVERTER_TARGET_TYPE)                           \
    class ARG_CONVERTER_NAME : public ::binary::components::NamedObjectConverter<ARG_CONVERTER_TARGET_TYPE> {  \
    public:                                                                                                    \
        ARG_CONVERTER_NAME(const ::binary::IGenerator& generator)                                              \
            : ::binary::components::NamedObjectConverter<ARG_CONVERTER_TARGET_TYPE>(GetContexts(generator)) {} \
                                                                                                               \
    private:                                                                                                   \
        using ConverterTargetType = ARG_CONVERTER_TARGET_TYPE;                                                 \
        using MemberInfo = ::binary::components::NamedObjectConverter<ARG_CONVERTER_TARGET_TYPE>::MemberInfo;  \
        using MemberInfoInitializer = std::function<MemberInfo(const ::binary::IGenerator&)>;                  \
                                                                                                               \
        static std::vector<MemberInfo> GetContexts(const ::binary::IGenerator& generator) {                    \
            static auto initializers = GetInitializers();                                                      \
            std::vector<MemberInfo> contexts;                                                                  \
            for (size_t i = 0; i < initializers.size(); i++) {                                                 \
                contexts.emplace_back(initializers.at(i)(generator));                                          \
            }                                                                                                  \
            return contexts;                                                                                   \
        }                                                                                                      \
                                                                                                               \
        static std::vector<MemberInfoInitializer> GetInitializers() {                                          \
            std::vector<MemberInfoInitializer> initializers;                                                   \
            GetInitializers(initializers);                                                                     \
            return initializers;                                                                               \
        }                                                                                                      \
                                                                                                               \
        static void GetInitializers(std::vector<MemberInfoInitializer>& initializers) {

#define BINARY_NAMED_OBJECT_CONVERTER_END() \
    }                                       \
    }                                       \
    ;

#define BINARY_NAMED_MEMBER(ARG_NAME)      \
    BINARY_NAMED_MEMBER_CUSTOM(            \
        #ARG_NAME, false,                  \
        item.ARG_NAME,                     \
        item.ARG_NAME = std::move(result), \
        ::binary::GetConverter<decltype(ConverterTargetType::ARG_NAME)>(generator))

#define BINARY_NAMED_MEMBER_CUSTOM(ARG_NAME, ARG_IS_OPTIONAL, ARG_GET_MEMBER_EXPRESSION, ARG_SET_MEMBER_EXPRESSION, ARG_GET_CONVERTER_EXPRESSION) \
    initializers.push_back([](auto& generator) {                                                                                                  \
        auto converter = ARG_GET_CONVERTER_EXPRESSION;                                                                                            \
        MemberInfo info{};                                                                                                                        \
        info.Name = ARG_NAME;                                                                                                                     \
        info.IsOptional = ARG_IS_OPTIONAL;                                                                                                        \
        info.Header = ::binary::Allocator::Invoke([&generator](auto& allocator) {                                                                 \
            ::binary::GetConverter<std::string>(generator)->Encode(allocator, ARG_NAME);                                                          \
        });                                                                                                                                       \
        info.EncodeWithLengthPrefix = [converter](auto& allocator, const auto& item) {                                                            \
            converter->EncodeWithLengthPrefix(allocator, ARG_GET_MEMBER_EXPRESSION);                                                              \
        };                                                                                                                                        \
        info.Decode = [converter](auto& item, const auto& span) {                                                                                 \
            auto result = converter->Decode(span);                                                                                                \
            ARG_SET_MEMBER_EXPRESSION;                                                                                                            \
        };                                                                                                                                        \
        return info;                                                                                                                              \
    })

#endif
