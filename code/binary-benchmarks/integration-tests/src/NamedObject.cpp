#include "Common.hpp"

#include <benchmark/benchmark.h>

#include <binary/Allocator.hpp>
#include <binary/GeneratorExtensions.hpp>
#include <binary/components/NamedObjectConverter.hpp>
#include <binary/experimental/Converter.hpp>

#include <concepts>
#include <cstddef>
#include <memory>
#include <span>

struct Type02NamedObjectSchema {
    static constexpr auto Members = std::tuple{
        ::binary::components::NamedMember{"Data", &Type02::Data},
        ::binary::components::NamedMember{"Tags", &Type02::Tags},
    };
};

struct Type01NamedObjectSchema {
    static constexpr auto Members = std::tuple{
        ::binary::components::NamedMember{"Id", &Type01::Id},
        ::binary::components::NamedMember{"Name", &Type01::Name},
        ::binary::components::NamedMember{"List", &Type01::List},
        ::binary::components::NamedMember{"Item", &Type01::Item},
    };
};

Type02NamedObjectSchema GetNamedObjectSchema(Type02*);
Type01NamedObjectSchema GetNamedObjectSchema(Type01*);

using Type02VirtualNamedObjectConverter = ::binary::components::NamedObjectConverter<Type02, Type02NamedObjectSchema>;
using Type01VirtualNamedObjectConverter = ::binary::components::NamedObjectConverter<Type01, Type01NamedObjectSchema>;

using Type01TemplateNamedObjectConverter = ::binary::experimental::Converter<Type01>;
using Type02TemplateNamedObjectConverter = ::binary::experimental::Converter<Type02>;

static_assert(std::same_as<Type01TemplateNamedObjectConverter, ::binary::experimental::components::NamedObjectConverter<Type01, Type01NamedObjectSchema>>);
static_assert(std::same_as<Type02TemplateNamedObjectConverter, ::binary::experimental::components::NamedObjectConverter<Type02, Type02NamedObjectSchema>>);

static void EncodeNamedObject(benchmark::State& state) {
    auto generator = GetTestGeneratorWithCommonTypes();
    ::binary::AddConverter<Type02VirtualNamedObjectConverter>(generator);
    ::binary::AddConverter<Type01VirtualNamedObjectConverter>(generator);
    auto converter = ::binary::GetConverter<Type01>(generator);
    auto data = GetTestDataOfType01();
    auto memory = std::make_unique<std::byte[]>(BufferLength);
    std::span<std::byte> span(memory.get(), BufferLength);

    for (auto _ : state) {
        ::binary::Allocator allocator(span);
        converter->Encode(allocator, data);
    }
}

static void EncodeTemplateNamedObject(benchmark::State& state) {
    auto data = GetTestDataOfType01();
    auto memory = std::make_unique<std::byte[]>(BufferLength);
    std::span<std::byte> span(memory.get(), BufferLength);

    for (auto _ : state) {
        ::binary::Allocator allocator(span);
        Type01TemplateNamedObjectConverter::Encode(allocator, data);
    }
}

static void DecodeNamedObject(benchmark::State& state) {
    auto generator = GetTestGeneratorWithCommonTypes();
    ::binary::AddConverter<Type02VirtualNamedObjectConverter>(generator);
    ::binary::AddConverter<Type01VirtualNamedObjectConverter>(generator);
    auto converter = ::binary::GetConverter<Type01>(generator);
    auto data = GetTestDataOfType01();
    ::binary::Allocator allocator;
    converter->Encode(allocator, data);
    const auto span = allocator.AsSpan();

    for (auto _ : state) {
        converter->Decode(span);
    }
}

static void DecodeTemplateNamedObject(benchmark::State& state) {
    auto data = GetTestDataOfType01();
    auto memory = ::binary::Allocator::Invoke([&](auto& allocator) {
        Type01TemplateNamedObjectConverter::Encode(allocator, data);
    });
    std::span<const std::byte> span(memory);

    for (auto _ : state) {
        Type01TemplateNamedObjectConverter::Decode(span);
    }
}

BENCHMARK(EncodeNamedObject)->Name("Encode Named Object");
BENCHMARK(EncodeTemplateNamedObject)->Name("Encode Template Named Object");
BENCHMARK(DecodeNamedObject)->Name("Decode Named Object");
BENCHMARK(DecodeTemplateNamedObject)->Name("Decode Template Named Object");
