#ifndef BINARY_COMPONENTS_TUPLEOBJECTCONVERTER_HPP
#define BINARY_COMPONENTS_TUPLEOBJECTCONVERTER_HPP

#include "binary/Converter.hpp"
#include "binary/internal/Converter.hpp"

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

    TupleObjectConverter(std::vector<MemberInfo>&& record)
        : Converter<T>(::binary::internal::GetConverterLength(record | std::views::transform([](const auto& info) { return info.Length; })))
        , record(std::move(record)) {}

    virtual void Encode(Allocator& allocator, const T& item) override {
        for (const auto& info : this->record) {
            info.Encode(allocator, item);
        }
    }

    virtual void EncodeAuto(Allocator& allocator, const T& item) override {
        for (const auto& info : this->record) {
            info.EncodeAuto(allocator, item);
        }
    }

    virtual T Decode(const std::span<const std::byte>& span) override {
        T result{};
        std::span<const std::byte> copy = span;
        for (const auto& info : this->record) {
            info.Decode(result, copy);
        }
        return result;
    }

    virtual T DecodeAuto(std::span<const std::byte>& span) override {
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
