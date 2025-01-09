#pragma once

#ifndef BINARY_COMPONENTS_NAMEDOBJECTCONVERTER_HPP
#define BINARY_COMPONENTS_NAMEDOBJECTCONVERTER_HPP

#include <string>
#include <vector>

#include "binary/Converter.hpp"
#include "binary/GeneratorExtensions.hpp"
#include "binary/IGenerator.hpp"
#include "binary/components/NamedObjectDecoder.hpp"

namespace binary::components {
template <typename T>
class NamedObjectConverter : public Converter<T> {
public:
    using EncodeWithLengthPrefixFunction = std::function<void(IConverter&, Allocator&, const T&)>;
    using DecodeFunction = std::function<void(T&, IConverter&, const std::span<const std::byte>&)>;
    using GetConverterFunction = std::function<std::shared_ptr<IConverter>(IGenerator&)>;

    struct MemberInfo {
        bool IsOptional = false;
        std::string Name;
        EncodeWithLengthPrefixFunction EncodeWithLengthPrefixFunction;
        DecodeFunction DecodeFunction;
        GetConverterFunction GetConverterFunction;
    };

    NamedObjectConverter(IGenerator& generator, const std::vector<MemberInfo>& contexts)
        : contexts(contexts) {
        auto encoding = GetConverter<std::string>(generator);
        for (size_t i = 0; i < contexts.size(); i++) {
            const auto& info = contexts.at(i);
            const auto& name = info.Name;
            auto head = Allocator::Invoke([&encoding, &name](auto& allocator) { encoding->Encode(allocator, name); });
            this->names.emplace_back(name);
            this->headers.emplace_back(head);
            this->converters.emplace_back(info.GetConverterFunction(generator));
        }
        this->decoder = std::make_unique<NamedObjectDecoder>(this->names, this->headers);
    }

    virtual void Encode(Allocator& allocator, const T& item) override {
        const auto& contexts = this->contexts;
        for (size_t i = 0; i < contexts.size(); i++) {
            const auto& info = contexts.at(i);
            const auto& head = this->headers.at(i);
            const auto& converter = this->converters.at(i);
            allocator.AppendWithLengthPrefix(head);
            info.EncodeWithLengthPrefixFunction(*converter, allocator, item);
        }
    }

    virtual T Decode(const std::span<const std::byte>& span) override {
        std::vector<std::tuple<bool, std::span<const std::byte>>> slices;
        this->decoder->Invoke(span, slices);

        T result{};
        const auto& contexts = this->contexts;
        for (size_t i = 0; i < contexts.size(); i++) {
            const auto& info = contexts.at(i);
            const auto& converter = this->converters.at(i);
            info.DecodeFunction(result, *converter, std::get<1>(slices.at(i)));
        }
        return result;
    }

private:
    const std::vector<MemberInfo>& contexts;
    std::vector<std::string> names;
    std::vector<std::vector<std::byte>> headers;
    std::vector<std::shared_ptr<IConverter>> converters;
    std::unique_ptr<NamedObjectDecoder> decoder;
};
}

#endif
