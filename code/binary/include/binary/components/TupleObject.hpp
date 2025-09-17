#ifndef BINARY_COMPONENTS_TUPLEOBJECT_HPP
#define BINARY_COMPONENTS_TUPLEOBJECT_HPP

#include "binary/GeneratorExtensions.hpp"
#include "binary/components/TupleObjectConverter.hpp"

#define BINARY_TUPLE_OBJECT_CONVERTER_INTERNAL_TYPE_DEFINE(ARG_CONVERTER_NAME, ARG_OBJECT_TYPE, ARG_CONVERTER_TEMPLATE_NAME, ARG_TEMPLATE_DEFINE) \
    ARG_TEMPLATE_DEFINE                                                                                                                           \
    class ARG_CONVERTER_NAME : public ::binary::components::TupleObjectConverter<ARG_OBJECT_TYPE> {                                               \
    public:                                                                                                                                       \
        ARG_CONVERTER_NAME(const ::binary::IGenerator& generator)                                                                                 \
            : ::binary::components::TupleObjectConverter<ARG_OBJECT_TYPE>(GetMemberInfoList(generator)) {}                                        \
                                                                                                                                                  \
    private:                                                                                                                                      \
        using ObjectType = ARG_OBJECT_TYPE;                                                                                                       \
        using MemberInfo = ::binary::components::TupleObjectConverter<ARG_OBJECT_TYPE>::MemberInfo;                                               \
        using MemberInfoInitializer = std::function<MemberInfo(const ::binary::IGenerator&, bool)>;                                               \
                                                                                                                                                  \
        static std::vector<MemberInfo> GetMemberInfoList(const ::binary::IGenerator& generator) {                                                 \
            static auto initializers = GetMemberInfoInitializerList();                                                                            \
            std::vector<MemberInfo> result;                                                                                                       \
            for (size_t i = 0; i < initializers.size(); i++) {                                                                                    \
                result.emplace_back(initializers.at(i)(generator, i == initializers.size() - 1));                                                 \
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

#define BINARY_TUPLE_OBJECT_CONVERTER(ARG_CONVERTER_NAME, ARG_OBJECT_TYPE) \
    BINARY_TUPLE_OBJECT_CONVERTER_INTERNAL_TYPE_DEFINE(                    \
        ARG_CONVERTER_NAME, ARG_OBJECT_TYPE,                               \
        ARG_CONVERTER_NAME, )

#define BINARY_TUPLE_OBJECT_CONVERTER_TEMPLATE(ARG_CONVERTER_NAME, ARG_TEMPLATE_TYPE_NAME) \
    BINARY_TUPLE_OBJECT_CONVERTER_INTERNAL_TYPE_DEFINE(                                    \
        ARG_CONVERTER_NAME, ARG_TEMPLATE_TYPE_NAME,                                        \
        ARG_CONVERTER_NAME<ARG_TEMPLATE_TYPE_NAME>, template <typename ARG_TEMPLATE_TYPE_NAME>)

#define BINARY_TUPLE_MEMBER(ARG_NAME)      \
    BINARY_TUPLE_MEMBER_CUSTOM(            \
        item.ARG_NAME,                     \
        item.ARG_NAME = std::move(result), \
        ::binary::GetConverter<decltype(ObjectType::ARG_NAME)>(generator))

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
