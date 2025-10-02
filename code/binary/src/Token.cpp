#include "binary/Token.hpp"

#include <cassert>
#include <format>
#include <stdexcept>

#include "binary/ConverterExtensions.hpp"

namespace binary {
Token::Token(const IGenerator& generator, const std::span<const std::byte>& span) noexcept
    : generator(generator), span(span), initialized(span.empty()) {}

typename Token::TokenValue Token::DecodeTokens() const noexcept {
    try {
        assert(this->initialized == false);
        assert(this->self.lock().get() == this);
        std::unordered_map<std::string, std::shared_ptr<Token>> tokens;
        std::span<const std::byte> copy = this->span;
        const auto& decode = this->decode;
        while (!copy.empty()) {
            auto header = ::binary::DecodeWithLengthPrefix(copy);
            auto buffer = ::binary::DecodeWithLengthPrefix(copy);
            auto source = decode(header);
            auto result = std::shared_ptr<Token>(new Token(this->generator, buffer));
            result->self = result;
            result->parent = this->self;
            result->decode = this->decode;
            tokens.emplace(std::move(source), std::move(result));
        }
        return {tokens, nullptr};
    } catch (...) {
        return {std::unordered_map<std::string, std::shared_ptr<Token>>{}, std::current_exception()};
    }
}

const typename Token::TokenValue& Token::GetTokens() const noexcept {
    if (this->initialized == false) {
        std::lock_guard locker(this->mutex);
        if (this->initialized == false) {
            this->intent = DecodeTokens();
            this->initialized = true;
        }
    }
    assert(this->initialized == true);
    assert(this->self.lock().get() == this);
    return this->intent;
}

const std::unordered_map<std::string, std::shared_ptr<Token>>& Token::Children() const {
    return std::get<0>(GetTokens());
}

const std::shared_ptr<Token>& Token::At(const std::string& key) const {
    const auto& values = GetTokens();
    const auto& tokens = std::get<0>(values);
    auto it = tokens.find(key);
    if (it != tokens.end()) {
        return it->second;
    }
    const auto& exception = std::get<1>(values);
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

std::shared_ptr<Token> Token::Create(const IGenerator& generator, const std::span<const std::byte>& span) {
    auto result = std::shared_ptr<Token>(new Token(generator, span));
    result->self = result;
    result->decode = [converter = ::binary::GetConverter<std::string>(generator)](const std::span<const std::byte>& span) { return converter->Decode(span); };
    return result;
}
}
