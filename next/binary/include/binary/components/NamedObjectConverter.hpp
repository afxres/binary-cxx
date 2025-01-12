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
            this->optional.emplace_back(info.IsOptional);
            this->contexts.emplace_back(info);
        }
        this->decoder = std::make_unique<NamedObjectDecoder>(this->optional, this->names, this->headers);
    }

    virtual void Encode(Allocator& allocator, const T& item) override {
        const auto& headers = this->headers;
        const auto& contexts = this->contexts;
        for (size_t i = 0; i < contexts.size(); i++) {
            allocator.AppendWithLengthPrefix(headers.at(i));
            contexts.at(i).EncodeWithLengthPrefix(allocator, item);
        }
    }

    virtual T Decode(const std::span<const std::byte>& span) override {
        std::vector<std::tuple<bool, std::span<const std::byte>>> slices;
        this->decoder->Invoke(span, slices);

        T result{};
        const auto& contexts = this->contexts;
        for (size_t i = 0; i < slices.size(); i++) {
            assert(std::get<0>(slices.at(i)) || this->optional.at(i));
            if (std::get<0>(slices.at(i))) {
                contexts.at(i).Decode(result, std::get<1>(slices.at(i)));
            }
        }
        return result;
    }

private:
    std::vector<bool> optional;
    std::vector<MemberInfo> contexts;
    std::vector<std::string> names;
    std::vector<std::vector<std::byte>> headers;
    std::unique_ptr<NamedObjectDecoder> decoder;
};
}

#endif
