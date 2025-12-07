#include "binary/Token.hpp"

#include <cassert>
#include <format>
#include <memory>
#include <set>
#include <stdexcept>
#include <string>

#include "binary/ConverterExtensions.hpp"

#define GetTokenIntent() (*static_cast<TokenIntent*>(this->intent.get()))

namespace binary {
struct TokenIntent {
    bool initialized;
    const IGenerator& generator;
    std::span<const std::byte> span;
    std::shared_ptr<Converter<std::string>> converter;
    std::exception_ptr exception;
    std::set<std::string> keys;
    std::map<std::string_view, Token> children;

    TokenIntent(const IGenerator& generator, const std::span<const std::byte>& span) noexcept
        : initialized(span.empty()), generator(generator), span(span) {}
};

void Token::UpdateIntent() const {
    auto& intent = GetTokenIntent();
    if (intent.initialized == false) [[unlikely]] {
        try {
            assert(intent.initialized == false);
            assert(intent.converter != nullptr);
            assert(intent.keys.empty());
            assert(intent.children.empty());
            std::span<const std::byte> copy = intent.span;
            const auto& converter = intent.converter;
            while (!copy.empty()) {
                auto header = ::binary::DecodeWithLengthPrefix(copy);
                auto buffer = ::binary::DecodeWithLengthPrefix(copy);
                auto source = converter->Decode(header);
                auto target = std::make_shared<TokenIntent>(intent.generator, buffer);
                target->converter = converter;
                if (auto result = intent.keys.emplace(std::move(source)); result.second) {
                    intent.children.emplace(*(result.first), Token(target));
                }
            }
        } catch (...) {
            intent.keys.clear();
            intent.children.clear();
            intent.exception = std::current_exception();
        }
        intent.initialized = true;
    }
    assert(intent.initialized);
    assert(intent.exception == nullptr || intent.keys.empty());
    assert(intent.exception == nullptr || intent.children.empty());
}

const IGenerator& Token::GetGenerator() const {
    return GetTokenIntent().generator;
}

Token::Token(const IGenerator& generator, const std::span<const std::byte>& span)
    : intent(std::make_shared<TokenIntent>(generator, span)) {
    GetTokenIntent().converter = ::binary::GetConverter<std::string>(generator);
}

const std::span<const std::byte>& Token::Span() const {
    return GetTokenIntent().span;
}

const std::map<std::string_view, Token>& Token::Children() const {
    UpdateIntent();
    return GetTokenIntent().children;
}

const Token& Token::At(const std::string_view& key) const {
    UpdateIntent();
    const auto& intent = GetTokenIntent();
    const auto& children = intent.children;
    if (auto it = children.find(key); it != children.end()) {
        assert(intent.keys.find(std::string(key))->data() == it->first.data());
        return it->second;
    }
    const auto& exception = intent.exception;
    std::string message = std::format("key '{}' not found", key);
    if (exception != nullptr) {
        try {
            std::rethrow_exception(exception);
        } catch (...) {
            std::throw_with_nested(std::invalid_argument(message));
        }
    }
    throw std::invalid_argument(message);
}
}
