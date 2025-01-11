#pragma once

#ifndef BINARY_COMPONENTS_TUPLEOBJECTCONVERTER_HPP
#define BINARY_COMPONENTS_TUPLEOBJECTCONVERTER_HPP

#include "binary/Converter.hpp"
#include "binary/IGenerator.hpp"

namespace binary::components {
template <typename T>
class TupleObjectConverter : public Converter<T> {
public:
    using EncodeFunction = std::function<void(bool, IConverter&, Allocator&, const T&)>;
    using DecodeFunction = std::function<void(bool, T&, IConverter&, std::span<const std::byte>&)>;
    using GetConverterFunction = std::function<std::shared_ptr<IConverter>(IGenerator&)>;

    struct MemberInfo {
        EncodeFunction Encode;
        DecodeFunction Decode;
        GetConverterFunction GetConverter;
    };

    TupleObjectConverter(IGenerator& generator, const std::vector<MemberInfo>& contexts)
        : contexts(contexts) {
        for (const auto& info : contexts) {
            this->converters.emplace_back(info.GetConverter(generator));
        }
    }

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
            const auto& converter = this->converters.at(i);
            info.Encode(automatic || i != contexts.size() - 1, *converter, allocator, item);
        }
    }

    T DecodeInternal(std::span<const std::byte>& span, bool automatic) {
        T result{};
        const auto& contexts = this->contexts;
        for (size_t i = 0; i < contexts.size(); i++) {
            const auto& info = contexts.at(i);
            const auto& converter = this->converters.at(i);
            info.Decode(automatic || i != contexts.size() - 1, result, *converter, span);
        }
        return result;
    }

    const std::vector<MemberInfo>& contexts;
    std::vector<std::shared_ptr<IConverter>> converters;
};
}

#endif
