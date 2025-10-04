#ifndef BINARY_TOKEN_HPP
#define BINARY_TOKEN_HPP

#include <map>
#include <optional>
#include <string_view>

#include "binary/GeneratorExtensions.hpp"

namespace binary {
class Token {
    struct Intent;
    const std::shared_ptr<Intent> intent;

    Token(const std::shared_ptr<Intent>& intent)
        : intent(intent) {};
    const Intent& GetIntent() const;
    const IGenerator& GetGenerator() const;

public:
    Token(const IGenerator& generator, const std::span<const std::byte>& span);
    const std::span<const std::byte>& Span() const;
    const std::optional<Token> Parent() const;
    const std::map<std::string_view, Token>& Children() const;
    const Token& At(const std::string_view& key) const;
    bool operator==(const Token&) const = default;

    template <typename T>
        requires std::same_as<T, std::remove_cv_t<T>>
    T As() const {
        return ::binary::GetConverterRawPtr<T>(GetGenerator())->Decode(Span());
    }
};
}

#endif
