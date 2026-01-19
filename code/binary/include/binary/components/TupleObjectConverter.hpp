#ifndef BINARY_COMPONENTS_TUPLEOBJECTCONVERTER_HPP
#define BINARY_COMPONENTS_TUPLEOBJECTCONVERTER_HPP

#include "binary/Converter.hpp"
#include "binary/internal/Define.hpp"
#include "binary/internal/Module.hpp"

namespace binary::components {
template <typename T>
class TupleObjectConverter : public Converter<T> {
public:
    using EncodeFunction = std::function<void(Allocator&, const T&)>;
    using DecodeFunction = std::function<void(T&, std::span<const std::byte>&)>;

    struct MemberInfo {
        size_t Length;
        EncodeFunction Encode;
        EncodeFunction EncodeAuto;
        DecodeFunction Decode;
        DecodeFunction DecodeAuto;
    };

    explicit TupleObjectConverter(std::vector<MemberInfo>&& record)
        : Converter<T>(::binary::internal::GetConverterLength(record | std::views::transform([](const auto& info) { return info.Length; })))
        , record(std::move(record)) {}

    BINARY_DEFINE_OVERRIDE_ENCODE_METHOD(T) {
        for (const auto& info : this->record) {
            info.Encode(allocator, item);
        }
    }

    BINARY_DEFINE_OVERRIDE_ENCODE_AUTO_METHOD(T) {
        for (const auto& info : this->record) {
            info.EncodeAuto(allocator, item);
        }
    }

    BINARY_DEFINE_OVERRIDE_DECODE_METHOD(T) {
        T result{};
        std::span<const std::byte> copy = span;
        for (const auto& info : this->record) {
            info.Decode(result, copy);
        }
        return result;
    }

    BINARY_DEFINE_OVERRIDE_DECODE_AUTO_METHOD(T) {
        T result{};
        for (const auto& info : this->record) {
            info.DecodeAuto(result, span);
        }
        return result;
    }

private:
    std::vector<MemberInfo> record;
};
}

#endif
