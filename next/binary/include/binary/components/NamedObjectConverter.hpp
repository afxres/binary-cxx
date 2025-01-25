#ifndef BINARY_COMPONENTS_NAMEDOBJECTCONVERTER_HPP
#define BINARY_COMPONENTS_NAMEDOBJECTCONVERTER_HPP

#include <string>
#include <vector>

#include "binary/Converter.hpp"
#include "binary/ConverterExtensions.hpp"
#include "binary/IGenerator.hpp"
#include "binary/components/NamedObjectDecoder.hpp"

namespace binary::components {
template <typename T>
class NamedObjectConverter : public Converter<T> {
public:
    using EncodeFunction = std::function<void(Allocator&, const T&)>;
    using DecodeFunction = std::function<void(T&, const std::span<const std::byte>&)>;

    struct MemberInfo {
        bool IsOptional = false;
        std::string Name;
        std::vector<std::byte> Header;
        EncodeFunction EncodeWithLengthPrefix;
        DecodeFunction Decode;
    };

    NamedObjectConverter(std::vector<MemberInfo>&& contexts) {
        for (const auto& info : contexts) {
            this->names.emplace_back(info.Name);
            this->headers.emplace_back(info.Header);
            this->optional.emplace_back(info.IsOptional);
        }
        this->decoder = std::make_unique<NamedObjectDecoder>(this->optional, this->names, this->headers);
        this->contexts = contexts;
    }

    virtual void Encode(Allocator& allocator, const T& item) override {
        const auto& headers = this->headers;
        const auto& contexts = this->contexts;
        for (size_t i = 0; i < contexts.size(); i++) {
            EncodeWithLengthPrefix(allocator, headers.at(i));
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
