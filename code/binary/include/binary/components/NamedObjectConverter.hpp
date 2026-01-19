#ifndef BINARY_COMPONENTS_NAMEDOBJECTCONVERTER_HPP
#define BINARY_COMPONENTS_NAMEDOBJECTCONVERTER_HPP

#include <cassert>

#include "binary/Converter.hpp"
#include "binary/ConverterExtensions.hpp"
#include "binary/components/NamedObjectDecoder.hpp"
#include "binary/internal/Define.hpp"

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

    explicit NamedObjectConverter(std::vector<MemberInfo>&& record)
        : record(std::move(record)) {
        for (const auto& info : this->record) {
            this->names.emplace_back(info.Name);
            this->headers.emplace_back(info.Header);
            this->optional.emplace_back(info.IsOptional);
        }
        this->decoder = std::make_unique<NamedObjectDecoder>(this->headers, this->names, this->optional);
    }

    BINARY_DEFINE_OVERRIDE_ENCODE_METHOD(T) {
        const auto& headers = this->headers;
        const auto& record = this->record;
        for (size_t i = 0; i < record.size(); i++) {
            EncodeWithLengthPrefix(allocator, headers.at(i));
            record.at(i).EncodeWithLengthPrefix(allocator, item);
        }
    }

    BINARY_DEFINE_OVERRIDE_DECODE_METHOD(T) {
        auto slices = this->decoder->Invoke(span);

        T result{};
        const auto& record = this->record;
        for (size_t i = 0; i < record.size(); i++) {
            const auto& intent = slices.at(i);
            assert(intent.data() != nullptr || this->optional.at(i));
            if (intent.data() != nullptr) {
                record.at(i).Decode(result, intent);
            }
        }
        return result;
    }

private:
    std::vector<uint8_t> optional;
    std::vector<MemberInfo> record;
    std::vector<std::string> names;
    std::vector<std::vector<std::byte>> headers;
    std::unique_ptr<NamedObjectDecoder> decoder;
};
}

#endif
