#ifndef BINARY_TOKEN_HPP
#define BINARY_TOKEN_HPP

#include <exception>
#include <string>
#include <tuple>
#include <unordered_map>

#include "binary/GeneratorExtensions.hpp"

namespace binary {
class Token {
private:
    using TokenValue = std::tuple<std::unordered_map<std::string, std::shared_ptr<Token>>, std::exception_ptr>;
    using DecodeDelegate = std::function<std::string(const std::span<const std::byte>&)>;

    const IGenerator& generator;
    const std::span<const std::byte> span;
    std::weak_ptr<Token> self;
    std::weak_ptr<Token> parent;
    DecodeDelegate decode;
    mutable bool initialized;
    mutable TokenValue intent;

    Token(const IGenerator& generator, const std::span<const std::byte>& span) noexcept;
    TokenValue DecodeTokens() const noexcept;
    const TokenValue& GetTokens() const noexcept;

public:
    const std::span<const std::byte>& Span() const { return this->span; }
    const std::weak_ptr<Token>& Parent() const { return this->parent; }
    const std::unordered_map<std::string, std::shared_ptr<Token>>& Children() const;
    const std::shared_ptr<Token>& At(const std::string& key) const;

    template <typename T>
        requires std::same_as<T, std::remove_cv_t<T>>
    T As() const {
        return ::binary::GetConverter<T>(this->generator)->Decode(this->span);
    }

    static std::shared_ptr<Token> Create(const IGenerator& generator, const std::span<const std::byte>& span);
};
}

#endif
