#include "Corpus.hpp"

#include <cstddef>
#include <cstdint>
#include <map>
#include <optional>
#include <set>
#include <string>
#include <tuple>
#include <vector>

#include <binary/Allocator.hpp>
#include <binary/Generator.hpp>
#include <binary/GeneratorExtensions.hpp>
#include <binary/components/NamedObjectConverter.hpp>
#include <binary/components/TupleObjectConverter.hpp>
#include <binary/converters/ContainerConverter.hpp>
#include <binary/converters/LittleEndianConverter.hpp>
#include <binary/converters/LittleEndianStringConverter.hpp>
#include <binary/converters/OptionalConverter.hpp>
#include <binary/converters/TupleConverter.hpp>
#include <binary/experimental/Converter.hpp>
#include <binary/experimental/components/NamedObjectConverter.hpp>
#include <binary/experimental/components/TupleObjectConverter.hpp>
#include <binary/experimental/converters/ContainerConverter.hpp>
#include <binary/experimental/converters/LittleEndianConverter.hpp>
#include <binary/experimental/converters/LittleEndianStringConverter.hpp>
#include <binary/experimental/converters/OptionalConverter.hpp>
#include <binary/experimental/converters/TupleConverter.hpp>
#include <binary/experimental/helpers/ConverterDecodeAutoMethodHelper.hpp>
#include <binary/experimental/helpers/ConverterEncodeAutoMethodHelper.hpp>

#include "Types.hpp"

namespace tests::binary::wire {
namespace {
#if defined(BINARY_HAS_INT128)
__extension__ using Int128 = __int128;
__extension__ using UInt128 = unsigned __int128;
#endif

::binary::Generator MakeGenerator() {
    ::binary::Generator generator;
    ::binary::AddConverter<::binary::converters::LittleEndianConverter<bool>>(generator);
    ::binary::AddConverter<::binary::converters::LittleEndianConverter<std::int8_t>>(generator);
    ::binary::AddConverter<::binary::converters::LittleEndianConverter<std::uint8_t>>(generator);
    ::binary::AddConverter<::binary::converters::LittleEndianConverter<std::int16_t>>(generator);
    ::binary::AddConverter<::binary::converters::LittleEndianConverter<std::uint16_t>>(generator);
    ::binary::AddConverter<::binary::converters::LittleEndianConverter<std::int32_t>>(generator);
    ::binary::AddConverter<::binary::converters::LittleEndianConverter<std::uint32_t>>(generator);
    ::binary::AddConverter<::binary::converters::LittleEndianConverter<std::int64_t>>(generator);
    ::binary::AddConverter<::binary::converters::LittleEndianConverter<std::uint64_t>>(generator);
#if defined(BINARY_HAS_INT128)
    ::binary::AddConverter<::binary::converters::LittleEndianConverter<Int128>>(generator);
    ::binary::AddConverter<::binary::converters::LittleEndianConverter<UInt128>>(generator);
#endif
    ::binary::AddConverter<::binary::converters::LittleEndianConverter<float>>(generator);
    ::binary::AddConverter<::binary::converters::LittleEndianConverter<double>>(generator);
    ::binary::AddConverter<::binary::converters::LittleEndianConverter<Color>>(generator);
    ::binary::AddConverter<::binary::converters::LittleEndianStringConverter<std::string>>(generator);
    ::binary::AddConverter<::binary::converters::OptionalConverter<std::optional<std::int32_t>>>(generator);
    ::binary::AddConverter<::binary::converters::TupleConverter<std::tuple<std::int32_t, std::string>>>(generator);
    ::binary::AddConverter<::binary::converters::TupleConverter<std::tuple<std::int32_t, std::int32_t>>>(generator);
    ::binary::AddConverter<::binary::converters::TupleConverter<std::tuple<std::int32_t, std::int32_t, std::string>>>(generator);
    ::binary::AddConverter<::binary::converters::TupleConverter<std::tuple<std::tuple<std::int32_t, std::string>, std::tuple<std::int32_t, std::int32_t>>>>(generator);
    ::binary::AddConverter<::binary::converters::TupleConverter<std::pair<const std::int32_t, std::string>>>(generator);
    ::binary::AddConverter<::binary::converters::TupleConverter<std::pair<std::int32_t, std::string>>>(generator);
    ::binary::AddConverter<::binary::converters::LittleEndianConverter<std::byte>>(generator);
    ::binary::AddConverter<::binary::converters::ContainerConverter<std::vector<std::byte>>>(generator);
    ::binary::AddConverter<::binary::converters::ContainerConverter<std::vector<std::int32_t>>>(generator);
    ::binary::AddConverter<::binary::converters::ContainerConverter<std::vector<std::string>>>(generator);
    ::binary::AddConverter<::binary::converters::ContainerConverter<std::vector<std::vector<std::int32_t>>>>(generator);
    ::binary::AddConverter<::binary::converters::ContainerConverter<std::vector<std::optional<std::int32_t>>>>(generator);
    ::binary::AddConverter<::binary::converters::ContainerConverter<std::vector<Color>>>(generator);
    ::binary::AddConverter<::binary::converters::ContainerConverter<std::map<std::int32_t, std::string>>>(generator);
    ::binary::AddConverter<::binary::converters::TupleConverter<std::pair<const std::int32_t, std::int32_t>>>(generator);
    ::binary::AddConverter<::binary::converters::ContainerConverter<std::map<std::int32_t, std::int32_t>>>(generator);
    ::binary::AddConverter<::binary::converters::ContainerConverter<std::set<std::int32_t>>>(generator);
    ::binary::AddConverter<::binary::components::NamedObjectConverter<Tiny, TinySchema>>(generator);
    ::binary::AddConverter<::binary::components::NamedObjectConverter<Person, PersonSchema>>(generator);
    ::binary::AddConverter<::binary::components::NamedObjectConverter<Mid, MidSchema>>(generator);
    ::binary::AddConverter<::binary::components::NamedObjectConverter<WithOpt, WithOptSchema>>(generator);
    ::binary::AddConverter<::binary::components::TupleObjectConverter<TupleTwoInt, TupleTwoIntSchema>>(generator);
    ::binary::AddConverter<::binary::components::TupleObjectConverter<TupleIntStr, TupleIntStrSchema>>(generator);
    return generator;
}

::binary::Generator& GetGenerator() {
    static ::binary::Generator generator = MakeGenerator();
    return generator;
}

std::string ToHex(const std::vector<std::byte>& bytes) {
    static constexpr char Digits[] = "0123456789abcdef";
    std::string result;
    result.reserve(bytes.size() * 2);
    for (const auto& item : bytes) {
        auto value = std::to_integer<unsigned>(item);
        result.push_back(Digits[value >> 4]);
        result.push_back(Digits[value & 0x0fU]);
    }
    return result;
}

template <typename T>
std::vector<std::byte> EncodeVirtual(const T& item, bool isAuto) {
    auto converter = ::binary::GetConverter<T>(GetGenerator());
    return ::binary::Allocator::Invoke([&converter, &item, isAuto](::binary::Allocator& allocator) {
        if (isAuto) {
            converter->EncodeAuto(allocator, item);
        } else {
            converter->Encode(allocator, item);
        }
    });
}

template <typename T>
std::vector<std::byte> EncodeTemplate(const T& item, bool isAuto) {
    using Converter = ::binary::experimental::Converter<T>;
    return ::binary::Allocator::Invoke([&item, isAuto](::binary::Allocator& allocator) {
        if (isAuto) {
            ::binary::experimental::helpers::ConverterEncodeAutoMethodHelper<Converter>::Invoke(allocator, item);
        } else {
            Converter::Encode(allocator, item);
        }
    });
}

std::vector<std::byte> FromHex(const std::string& hex) {
    static constexpr auto Digit = [](char c) -> unsigned {
        if (c >= '0' && c <= '9') {
            return static_cast<unsigned>(c - '0');
        }
        return static_cast<unsigned>(c - 'a') + 10;
    };
    std::vector<std::byte> result;
    result.reserve(hex.size() / 2);
    for (size_t i = 0; i + 1 < hex.size(); i += 2) {
        result.push_back(static_cast<std::byte>((Digit(hex[i]) << 4) | Digit(hex[i + 1])));
    }
    return result;
}

template <typename T>
T DecodeVirtual(const std::vector<std::byte>& bytes, bool isAuto) {
    auto converter = ::binary::GetConverter<T>(GetGenerator());
    if (isAuto) {
        std::span<const std::byte> span(bytes);
        return converter->DecodeAuto(span);
    }
    return converter->Decode(std::span<const std::byte>(bytes));
}

template <typename T>
T DecodeTemplate(const std::vector<std::byte>& bytes, bool isAuto) {
    using Converter = ::binary::experimental::Converter<T>;
    if (isAuto) {
        std::span<const std::byte> span(bytes);
        return ::binary::experimental::helpers::ConverterDecodeAutoMethodHelper<Converter>::Invoke(span);
    }
    return Converter::Decode(std::span<const std::byte>(bytes));
}

template <typename T>
std::function<std::string(const std::string& bare, const std::string& auto_)> MakeVerify(const T& value) {
    return [value](const std::string& bare, const std::string& auto_) -> std::string {
        try {
            auto bareBytes = FromHex(bare);
            if (DecodeVirtual<T>(bareBytes, false) != value) {
                return "virtual Decode produced a different value";
            }
            if (DecodeTemplate<T>(bareBytes, false) != value) {
                return "template Decode produced a different value";
            }
        } catch (const std::exception& ex) {
            return std::string("Decode failed: ") + ex.what();
        }

        try {
            auto autoBytes = FromHex(auto_);
            if (DecodeVirtual<T>(autoBytes, true) != value) {
                return "virtual DecodeAuto produced a different value";
            }
            if (DecodeTemplate<T>(autoBytes, true) != value) {
                return "template DecodeAuto produced a different value";
            }
        } catch (const std::exception& ex) {
            return std::string("DecodeAuto failed: ") + ex.what();
        }

        return {};
    };
}

template <typename T>
void Add(std::map<std::string, Encoded>& out, std::string name, const T& value) {
    out.emplace(
        std::move(name),
        Encoded{
            ToHex(EncodeVirtual(value, false)),
            ToHex(EncodeVirtual(value, true)),
            ToHex(EncodeTemplate(value, false)),
            ToHex(EncodeTemplate(value, true)),
            MakeVerify(value),
        }
    );
}

std::string Repeat(const std::string& unit, size_t count) {
    std::string result;
    result.reserve(unit.size() * count);
    for (size_t i = 0; i < count; ++i) {
        result += unit;
    }
    return result;
}

std::map<std::string, Encoded> MakeEntries() {
    std::map<std::string, Encoded> out;

    Add(out, "bool_true", true);
    Add(out, "bool_false", false);
    Add(out, "u8_0", std::uint8_t{0});
    Add(out, "u8_255", std::uint8_t{255});
    Add(out, "i8_neg128", std::int8_t{-128});
    Add(out, "i8_neg1", std::int8_t{-1});
    Add(out, "i8_127", std::int8_t{127});
    Add(out, "u16_0", std::uint16_t{0});
    Add(out, "u16_60000", std::uint16_t{60000});
    Add(out, "u16_max", std::uint16_t{65535});
    Add(out, "i16_min", std::int16_t{-32768});
    Add(out, "i16_neg2", std::int16_t{-2});
    Add(out, "i16_0", std::int16_t{0});
    Add(out, "i16_max", std::int16_t{32767});
    Add(out, "u32_0", std::uint32_t{0});
    Add(out, "u32_max", std::uint32_t{4294967295U});
    Add(out, "i32_min", std::int32_t{-2147483647 - 1});
    Add(out, "i32_neg7", std::int32_t{-7});
    Add(out, "i32_0", std::int32_t{0});
    Add(out, "i32_42", std::int32_t{42});
    Add(out, "i32_max", std::int32_t{2147483647});
    Add(out, "u64_0", std::uint64_t{0});
    Add(out, "u64_max", std::uint64_t{18446744073709551615ULL});
    Add(out, "i64_min", std::int64_t{-9223372036854775807LL - 1});
    Add(out, "i64_neg2", std::int64_t{-2});
    Add(out, "i64_0", std::int64_t{0});
    Add(out, "i64_max", std::int64_t{9223372036854775807LL});
#if defined(BINARY_HAS_INT128)
    Add(out, "u128_0", UInt128{0});
    Add(out, "u128_max", static_cast<UInt128>(~UInt128{0}));
    Add(out, "i128_min", static_cast<Int128>(Int128{1} << 127));
    Add(out, "i128_neg1", Int128{-1});
    Add(out, "i128_0", Int128{0});
    Add(out, "i128_max", static_cast<Int128>((static_cast<UInt128>(Int128{-1}) >> 1)));
#endif
    Add(out, "f32_0", 0.0F);
    Add(out, "f32_neg_zero", -0.0F);
    Add(out, "f32_1_5", 1.5F);
    Add(out, "f64_0", 0.0);
    Add(out, "f64_neg_zero", -0.0);
    Add(out, "f64_1_5", 1.5);
    Add(out, "string_empty", std::string{});
    Add(out, "string_16a", Repeat("a", 16));
    Add(out, "string_17a", Repeat("a", 17));
    Add(out, "string_41a", Repeat("a", 41));
    Add(out, "string_42a", Repeat("a", 42));
    Add(out, "string_127a", Repeat("a", 127));
    Add(out, "string_128a", Repeat("a", 128));
    Add(out, "string_20zh", Repeat("中", 20));
    Add(out, "string_2emoji", Repeat("😀", 2));
    Add(out, "i32opt_none", std::optional<std::int32_t>{});
    Add(out, "i32opt_some5", std::optional<std::int32_t>{5});
    Add(out, "named_with_opt_none", WithOpt{});
    Add(out, "named_with_opt_some", WithOpt{5});
    Add(out, "tuple_i32_str", std::tuple<std::int32_t, std::string>{1, "a"});
    Add(out, "tuple_three", std::tuple<std::int32_t, std::int32_t, std::string>{1, 2, "c"});
    Add(out, "tuple_nested_pair",
        std::tuple<std::tuple<std::int32_t, std::string>, std::tuple<std::int32_t, std::int32_t>>{
            std::tuple<std::int32_t, std::string>{1, "a"},
            std::tuple<std::int32_t, std::int32_t>{2, 3},
        });
    Add(out, "vec_i32_3", std::vector<std::int32_t>{1, 2, 3});
    Add(out, "vec_i32_5", std::vector<std::int32_t>{1, 2, 3, 4, 5});
    Add(out, "vec_string_4x4", std::vector<std::string>{"aaaa", "bbbb", "cccc", "dddd"});
    Add(out, "vec_vec_i32", std::vector<std::vector<std::int32_t>>{{1}, {2}});
    Add(out, "vec_i32opt", std::vector<std::optional<std::int32_t>>{std::nullopt, 5});
    Add(out, "vec_i32opt_none", std::vector<std::optional<std::int32_t>>{std::nullopt});
    Add(out, "sortedset_i32_5", std::set<std::int32_t>{1, 2, 3, 4, 5});
    Add(out, "sorteddictionary_i32_str", std::map<std::int32_t, std::string>{{1, "a"}, {2, "b"}});
    Add(out, "sorteddictionary_i32_i32_5", std::map<std::int32_t, std::int32_t>{{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}});
    Add(out, "sorteddictionary_i32_str_4", std::map<std::int32_t, std::string>{{1, "a"}, {2, "b"}, {3, "c"}, {4, "d"}});
    Add(out, "kvp_i32_str", std::pair<std::int32_t, std::string>{1, "a"});
    Add(out, "bytes_5", std::vector<std::byte>{std::byte{1}, std::byte{2}, std::byte{3}, std::byte{4}, std::byte{5}});
    Add(out, "enum_green", Color::Green);
    Add(out, "vec_enum", std::vector<Color>{Color::Red, Color::Green});
    Add(out, "named_tiny", Tiny{7});
    Add(out, "named_person", Person{42, "Bob"});
    Add(out, "named_mid", Mid{1, 2, 3});
    Add(out, "tupleobj_two_int", TupleTwoInt{1, 2});
    Add(out, "tupleobj_int_str", TupleIntStr{1, "a"});

    return out;
}
}

const std::map<std::string, Encoded>& Entries() {
    static const std::map<std::string, Encoded> entries = MakeEntries();
    return entries;
}
}
