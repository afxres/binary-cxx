#ifndef BINARY_TOKEN_HPP
#define BINARY_TOKEN_HPP

#include <map>
#include <string_view>

#include "binary/GeneratorExtensions.hpp"

namespace binary {
class Token {
    const std::shared_ptr<void> intent;

    Token(const std::shared_ptr<void>& intent)
        : intent(intent) {};
    void UpdateIntent() const;
    [[nodiscard]] const IGenerator& GetGenerator() const;

public:
    Token(const IGenerator& generator, const std::span<const std::byte>& span);
    [[nodiscard]] const std::span<const std::byte>& Span() const;
    [[nodiscard]] const std::map<std::string_view, Token>& Children() const;
    [[nodiscard]] const Token& At(const std::string_view& key) const;

    template <typename T>
        requires std::same_as<T, std::remove_cv_t<T>>
    T As() const {
        return ::binary::GetConverterRawPtr<T>(GetGenerator())->Decode(Span());
    }
};
}

#endif
