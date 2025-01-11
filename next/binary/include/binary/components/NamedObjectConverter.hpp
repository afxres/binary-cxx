#pragma once

#ifndef BINARY_COMPONENTS_NAMEDOBJECTCONVERTER_HPP
#define BINARY_COMPONENTS_NAMEDOBJECTCONVERTER_HPP

#include <string>
#include <vector>

#include "binary/Converter.hpp"
#include "binary/IGenerator.hpp"
#include "binary/components/NamedObjectDecoder.hpp"

namespace binary::components {
template <typename T>
class NamedObjectConverter : public Converter<T> {
public:
    struct MemberInfo;
    using EncodeFunction = std::function<void(Allocator&, const T&)>;
    using DecodeFunction = std::function<void(T&, const std::span<const std::byte>&)>;
    using MemberInfoInitializer = std::function<MemberInfo(IGenerator&)>;

    struct MemberInfo {
        bool IsOptional = false;
        std::string Name;
        EncodeFunction EncodeWithLengthPrefix;
        DecodeFunction Decode;
    };

    NamedObjectConverter(IGenerator& generator, const std::vector<MemberInfoInitializer>& initializers) {
        auto encoding = GetConverter<std::string>(generator);
        for (size_t i = 0; i < initializers.size(); i++) {
            const auto& initializer = initializers.at(i);
            auto info = initializer(generator);
            const auto& name = info.Name;
            auto head = Allocator::Invoke([&encoding, &name](auto& allocator) { encoding->Encode(allocator, name); });
            this->names.emplace_back(name);
            this->headers.emplace_back(head);
            this->contexts.emplace_back(info);
        }
        this->decoder = std::make_unique<NamedObjectDecoder>(this->names, this->headers);
    }

    virtual void Encode(Allocator& allocator, const T& item) override {
        const auto& contexts = this->contexts;
        for (size_t i = 0; i < contexts.size(); i++) {
            const auto& info = contexts.at(i);
            const auto& head = this->headers.at(i);
            allocator.AppendWithLengthPrefix(head);
            info.EncodeWithLengthPrefix(allocator, item);
        }
    }

    virtual T Decode(const std::span<const std::byte>& span) override {
        std::vector<std::tuple<bool, std::span<const std::byte>>> slices;
        this->decoder->Invoke(span, slices);

        T result{};
        const auto& contexts = this->contexts;
        for (size_t i = 0; i < contexts.size(); i++) {
            const auto& info = contexts.at(i);
            info.Decode(result, std::get<1>(slices.at(i)));
        }
        return result;
    }

private:
    std::vector<MemberInfo> contexts;
    std::vector<std::string> names;
    std::vector<std::vector<std::byte>> headers;
    std::unique_ptr<NamedObjectDecoder> decoder;
};
}

#endif
