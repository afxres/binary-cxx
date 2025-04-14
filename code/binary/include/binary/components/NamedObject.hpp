#ifndef BINARY_COMPONENTS_NAMEDOBJECT_HPP
#define BINARY_COMPONENTS_NAMEDOBJECT_HPP

#include "binary/GeneratorExtensions.hpp"
#include "binary/components/NamedObjectConverter.hpp"

#define BINARY_NAMED_OBJECT_CONVERTER_INTERNAL_TYPE_DEFINE(ARG_CONVERTER_NAME, ARG_OBJECT_TYPE, ARG_CONVERTER_TEMPLATE_NAME, ARG_TEMPLATE_DEFINE) \
    ARG_TEMPLATE_DEFINE                                                                                                                           \
    class ARG_CONVERTER_NAME : public ::binary::components::NamedObjectConverter<ARG_OBJECT_TYPE> {                                               \
    public:                                                                                                                                       \
        ARG_CONVERTER_NAME(const ::binary::IGenerator& generator)                                                                                 \
            : ::binary::components::NamedObjectConverter<ARG_OBJECT_TYPE>(GetMemberInfoList(generator)) {}                                        \
                                                                                                                                                  \
    private:                                                                                                                                      \
        using ObjectType = ARG_OBJECT_TYPE;                                                                                                       \
        using MemberInfo = ::binary::components::NamedObjectConverter<ARG_OBJECT_TYPE>::MemberInfo;                                               \
        using MemberInfoInitializer = std::function<MemberInfo(const ::binary::IGenerator&)>;                                                     \
                                                                                                                                                  \
        static std::vector<MemberInfo> GetMemberInfoList(const ::binary::IGenerator& generator) {                                                 \
            static auto initializers = GetMemberInfoInitializerList();                                                                            \
            std::vector<MemberInfo> result;                                                                                                       \
            for (size_t i = 0; i < initializers.size(); i++) {                                                                                    \
                result.emplace_back(initializers.at(i)(generator));                                                                               \
            }                                                                                                                                     \
            return result;                                                                                                                        \
        }                                                                                                                                         \
                                                                                                                                                  \
        static std::vector<MemberInfoInitializer> GetMemberInfoInitializerList() {                                                                \
            std::vector<MemberInfoInitializer> initializers;                                                                                      \
            GetMemberInfoInitializerList(initializers);                                                                                           \
            return initializers;                                                                                                                  \
        }                                                                                                                                         \
                                                                                                                                                  \
        static void GetMemberInfoInitializerList(std::vector<MemberInfoInitializer>& initializers);                                               \
    };                                                                                                                                            \
                                                                                                                                                  \
    ARG_TEMPLATE_DEFINE                                                                                                                           \
    void ARG_CONVERTER_TEMPLATE_NAME::GetMemberInfoInitializerList(std::vector<MemberInfoInitializer>& initializers)

#define BINARY_NAMED_OBJECT_CONVERTER(ARG_CONVERTER_NAME, ARG_OBJECT_TYPE) \
    BINARY_NAMED_OBJECT_CONVERTER_INTERNAL_TYPE_DEFINE(ARG_CONVERTER_NAME, ARG_OBJECT_TYPE, ARG_CONVERTER_NAME, )

#define BINARY_NAMED_OBJECT_CONVERTER_TEMPLATE(ARG_CONVERTER_NAME, ARG_TEMPLATE_TYPE_NAME) \
    BINARY_NAMED_OBJECT_CONVERTER_INTERNAL_TYPE_DEFINE(ARG_CONVERTER_NAME, ARG_TEMPLATE_TYPE_NAME, ARG_CONVERTER_NAME<ARG_TEMPLATE_TYPE_NAME>, template <typename ARG_TEMPLATE_TYPE_NAME>)

#define BINARY_NAMED_MEMBER(ARG_NAME)      \
    BINARY_NAMED_MEMBER_CUSTOM(            \
        #ARG_NAME, false,                  \
        item.ARG_NAME,                     \
        item.ARG_NAME = std::move(result), \
        ::binary::GetConverter<decltype(ObjectType::ARG_NAME)>(generator))

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
