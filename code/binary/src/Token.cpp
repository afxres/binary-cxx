#include "binary/Token.hpp"

#include <cassert>
#include <format>
#include <set>
#include <stdexcept>
#include <string>

#include "binary/ConverterExtensions.hpp"

namespace binary {
struct Token::Intent {
    bool initialized;
    const IGenerator& generator;
    std::span<const std::byte> span;
    std::weak_ptr<Intent> parent;
    std::shared_ptr<Converter<std::string>> converter;
    std::exception_ptr exception;
    std::set<std::string> keys;
    std::map<std::string_view, Token> children;

    Intent(const IGenerator& generator, const std::span<const std::byte>& span) noexcept
        : initialized(span.empty()), generator(generator), span(span) {}
};

const Token::Intent& Token::GetIntent() const {
    auto& intent = *this->intent;
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
                auto target = std::shared_ptr<Intent>(new Intent(intent.generator, buffer));
                target->converter = converter;
                target->parent = this->intent;
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
    return intent;
}

const IGenerator& Token::GetGenerator() const {
    return this->intent->generator;
}

Token::Token(const IGenerator& generator, const std::span<const std::byte>& span)
    : intent(std::shared_ptr<Intent>(new Intent(generator, span))) {
    this->intent->converter = ::binary::GetConverter<std::string>(generator);
}

const std::span<const std::byte>& Token::Span() const {
    return this->intent->span;
}

const std::optional<Token> Token::Parent() const {
    if (auto parent = this->intent->parent.lock(); parent != nullptr) {
        return std::make_optional<Token>(std::move(parent));
    } else {
        return std::nullopt;
    }
}

const std::map<std::string_view, Token>& Token::Children() const {
    return GetIntent().children;
}

const Token& Token::At(const std::string_view& key) const {
    const auto& intent = GetIntent();
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
