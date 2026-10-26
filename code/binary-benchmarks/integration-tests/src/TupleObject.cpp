#include "Common.hpp"

#include <benchmark/benchmark.h>

#include <binary/Allocator.hpp>
#include <binary/GeneratorExtensions.hpp>
#include <binary/components/TupleObjectConverter.hpp>
#include <binary/experimental/Converter.hpp>

#include <concepts>
#include <cstddef>
#include <memory>
#include <span>

struct Type02TupleObjectSchema {
    static constexpr auto Members = std::tuple{
        ::binary::components::TupleMember{&Type02::Data},
        ::binary::components::TupleMember{&Type02::Tags},
    };
};

struct Type01TupleObjectSchema {
    static constexpr auto Members = std::tuple{
        ::binary::components::TupleMember{&Type01::Id},
        ::binary::components::TupleMember{&Type01::Name},
        ::binary::components::TupleMember{&Type01::List},
        ::binary::components::TupleMember{&Type01::Item},
    };
};

Type02TupleObjectSchema GetTupleObjectSchema(Type02*);
Type01TupleObjectSchema GetTupleObjectSchema(Type01*);

using Type02VirtualTupleObjectConverter = ::binary::components::TupleObjectConverter<Type02, Type02TupleObjectSchema>;
using Type01VirtualTupleObjectConverter = ::binary::components::TupleObjectConverter<Type01, Type01TupleObjectSchema>;

using Type01TemplateTupleObjectConverter = ::binary::experimental::Converter<Type01>;
using Type02TemplateTupleObjectConverter = ::binary::experimental::Converter<Type02>;

static_assert(std::same_as<Type01TemplateTupleObjectConverter, ::binary::experimental::components::TupleObjectConverter<Type01, Type01TupleObjectSchema>>);
static_assert(std::same_as<Type02TemplateTupleObjectConverter, ::binary::experimental::components::TupleObjectConverter<Type02, Type02TupleObjectSchema>>);

static void EncodeTupleObject(benchmark::State& state) {
    auto generator = GetTestGeneratorWithCommonTypes();
    ::binary::AddConverter<Type02VirtualTupleObjectConverter>(generator);
    ::binary::AddConverter<Type01VirtualTupleObjectConverter>(generator);
    auto converter = ::binary::GetConverter<Type01>(generator);
    auto data = GetTestDataOfType01();
    auto memory = std::make_unique<std::byte[]>(BufferLength);
    std::span<std::byte> span(memory.get(), BufferLength);

    for (auto _ : state) {
        ::binary::Allocator allocator(span);
        converter->Encode(allocator, data);
    }
}

static void EncodeTemplateTupleObject(benchmark::State& state) {
    auto data = GetTestDataOfType01();
    auto memory = std::make_unique<std::byte[]>(BufferLength);
    std::span<std::byte> span(memory.get(), BufferLength);

    for (auto _ : state) {
        ::binary::Allocator allocator(span);
        Type01TemplateTupleObjectConverter::Encode(allocator, data);
    }
}

static void DecodeTupleObject(benchmark::State& state) {
    auto generator = GetTestGeneratorWithCommonTypes();
    ::binary::AddConverter<Type02VirtualTupleObjectConverter>(generator);
    ::binary::AddConverter<Type01VirtualTupleObjectConverter>(generator);
    auto converter = ::binary::GetConverter<Type01>(generator);
    auto data = GetTestDataOfType01();
    ::binary::Allocator allocator;
    converter->Encode(allocator, data);
    const auto span = allocator.AsSpan();

    for (auto _ : state) {
        converter->Decode(span);
    }
}

static void DecodeTemplateTupleObject(benchmark::State& state) {
    auto data = GetTestDataOfType01();
    auto memory = ::binary::Allocator::Invoke([&](auto& allocator) {
        Type01TemplateTupleObjectConverter::Encode(allocator, data);
    });
    std::span<const std::byte> span(memory);

    for (auto _ : state) {
        Type01TemplateTupleObjectConverter::Decode(span);
    }
}

BENCHMARK(EncodeTupleObject)->Name("Encode Tuple Object");
BENCHMARK(EncodeTemplateTupleObject)->Name("Encode Template Tuple Object");
BENCHMARK(DecodeTupleObject)->Name("Decode Tuple Object");
BENCHMARK(DecodeTemplateTupleObject)->Name("Decode Template Tuple Object");
