#ifndef BINARY_COMPONENTS_TUPLEOBJECTCONVERTER_HPP
#define BINARY_COMPONENTS_TUPLEOBJECTCONVERTER_HPP

#include "binary/Converter.hpp"
#include "binary/IGenerator.hpp"

namespace binary::components {
template <typename T>
class TupleObjectConverter : public Converter<T> {
public:
    using EncodeFunction = std::function<void(bool, Allocator&, const T&)>;
    using DecodeFunction = std::function<void(bool, T&, std::span<const std::byte>&)>;

    struct MemberInfo {
        size_t Length;
        EncodeFunction Encode;
        DecodeFunction Decode;
    };

    TupleObjectConverter(std::vector<MemberInfo>&& contexts)
        : Converter<T>(GetConverterLength(contexts | std::views::transform([](const auto& info) { return info.Length; }))), contexts(contexts) {}

    virtual void Encode(Allocator& allocator, const T& item) override {
        EncodeInternal(allocator, item, false);
    }

    virtual void EncodeAuto(Allocator& allocator, const T& item) override {
        EncodeInternal(allocator, item, true);
    }

    virtual T Decode(const std::span<const std::byte>& span) override {
        std::span<const std::byte> copy = span;
        return DecodeInternal(copy, false);
    }

    virtual T DecodeAuto(std::span<const std::byte>& span) override {
        return DecodeInternal(span, true);
    }

private:
    void EncodeInternal(Allocator& allocator, const T& item, bool automatic) {
        const auto& contexts = this->contexts;
        for (size_t i = 0; i < contexts.size(); i++) {
            const auto& info = contexts.at(i);
            info.Encode(automatic || i != contexts.size() - 1, allocator, item);
        }
    }

    T DecodeInternal(std::span<const std::byte>& span, bool automatic) {
        T result{};
        const auto& contexts = this->contexts;
        for (size_t i = 0; i < contexts.size(); i++) {
            const auto& info = contexts.at(i);
            info.Decode(automatic || i != contexts.size() - 1, result, span);
        }
        return result;
    }

    std::vector<MemberInfo> contexts;
};
}

#endif
