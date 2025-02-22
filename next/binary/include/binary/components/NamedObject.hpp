#ifndef BINARY_COMPONENTS_NAMEDOBJECT_HPP
#define BINARY_COMPONENTS_NAMEDOBJECT_HPP

#include "binary/GeneratorExtensions.hpp"
#include "binary/components/NamedObjectConverter.hpp"

#define BINARY_NAMED_OBJECT_CONVERTER(ARG_TYPE, ARG_CONVERTER_NAME)                           \
    class ARG_CONVERTER_NAME : public ::binary::components::NamedObjectConverter<ARG_TYPE> {  \
    public:                                                                                   \
        ARG_CONVERTER_NAME(const ::binary::IGenerator& generator)                             \
            : NamedObjectConverter<ARG_TYPE>(GetContexts(generator)) {}                       \
                                                                                              \
    private:                                                                                  \
        using GenericArgument = ARG_TYPE;                                                     \
        using MemberInfoInitializer = std::function<MemberInfo(const ::binary::IGenerator&)>; \
                                                                                              \
        static std::vector<MemberInfo> GetContexts(const ::binary::IGenerator& generator) {   \
            std::vector<MemberInfo> contexts;                                                 \
            const auto& initializers = GetInitializers();                                     \
            for (size_t i = 0; i < initializers.size(); i++) {                                \
                contexts.emplace_back(initializers.at(i)(generator));                         \
            }                                                                                 \
            return contexts;                                                                  \
        }                                                                                     \
                                                                                              \
        static const std::vector<MemberInfoInitializer>& GetInitializers() {                  \
            static bool initialized = false;                                                  \
            static std::vector<MemberInfoInitializer> initializers;                           \
            if (initialized == false) {                                                       \
                initialized = true;

#define BINARY_NAMED_OBJECT_CONVERTER_END() \
    }                                       \
    return initializers;                    \
    }                                       \
    }                                       \
    ;

#define BINARY_NAMED_MEMBER(ARG_NAME)      \
    BINARY_NAMED_MEMBER_CUSTOM(            \
        #ARG_NAME, false,                  \
        item.ARG_NAME,                     \
        item.ARG_NAME = std::move(result), \
        GetConverter<decltype(GenericArgument::ARG_NAME)>(generator))

#define BINARY_NAMED_MEMBER_CUSTOM(ARG_NAME, ARG_IS_OPTIONAL, ARG_GET_MEMBER_EXPRESSION, ARG_SET_MEMBER_EXPRESSION, ARG_GET_CONVERTER_EXPRESSION) \
    initializers.push_back([]([[maybe_unused]] auto& generator) {                                                                                 \
        auto encoding = GetConverter<std::string>(generator);                                                                                     \
        auto converter = ARG_GET_CONVERTER_EXPRESSION;                                                                                            \
        MemberInfo info{};                                                                                                                        \
        info.Name = ARG_NAME;                                                                                                                     \
        info.Header = ::binary::Allocator::Invoke([&encoding](auto& allocator) { encoding->Encode(allocator, ARG_NAME); });                       \
        info.IsOptional = ARG_IS_OPTIONAL;                                                                                                        \
        info.EncodeWithLengthPrefix = [converter](auto& allocator, const auto& item) {                                                            \
            converter->EncodeWithLengthPrefix(allocator, ARG_GET_MEMBER_EXPRESSION);                                                              \
        };                                                                                                                                        \
        info.Decode = [converter](auto& item, const auto& span) {                                                                                 \
            auto result = converter->Decode(span);                                                                                                \
            ARG_SET_MEMBER_EXPRESSION;                                                                                                            \
        };                                                                                                                                        \
        return info;                                                                                                                              \
    });

#endif
