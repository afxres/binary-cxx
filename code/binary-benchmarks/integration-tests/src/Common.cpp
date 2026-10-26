#include "Common.hpp"

#include <benchmark/benchmark.h>

#include <concepts>
#include <cstddef>
#include <memory>
#include <span>
#include <string>
#include <vector>

#include <binary/Allocator.hpp>
#include <binary/Generator.hpp>
#include <binary/GeneratorExtensions.hpp>
#include <binary/converters/ContainerConverter.hpp>
#include <binary/converters/LittleEndianConverter.hpp>
#include <binary/converters/LittleEndianStringConverter.hpp>
#include <binary/converters/TupleConverter.hpp>
#include <binary/experimental/Converter.hpp>

using Type01TemplateConverter = ::binary::experimental::Converter<Type01>;
using Type02TemplateConverter = ::binary::experimental::Converter<Type02>;
using TypeX1TemplateConverter = ::binary::experimental::Converter<TypeX1>;
using TypeX2TemplateConverter = ::binary::experimental::Converter<TypeX2>;

static_assert(std::same_as<Type01TemplateConverter, ::binary::experimental::converters::TupleConverter<Type01>>);
static_assert(std::same_as<Type02TemplateConverter, ::binary::experimental::converters::TupleConverter<Type02>>);
static_assert(std::same_as<TypeX1TemplateConverter, ::binary::experimental::converters::TupleConverter<TypeX1>>);
static_assert(std::same_as<TypeX2TemplateConverter, ::binary::experimental::converters::TupleConverter<TypeX2>>);

TypeX1 GetTestDataOfTypeX1() {
    TypeX2 item = {2.2, {"one", "two", "three"}};
    TypeX1 data = {1024, "csharp", {7, 11, 555, 1313}, item};
    return data;
}

Type01 GetTestDataOfType01() {
    Type02 item{};
    item.Data = 2.2;
    item.Tags = {"one", "two", "three"};
    Type01 data{};
    data.Id = 1024;
    data.Name = "csharp";
    data.List = {7, 11, 555, 1313};
    data.Item = item;
    return data;
}

::binary::Generator GetTestGeneratorWithCommonTypes() {
    ::binary::Generator generator;
    ::binary::AddConverter<::binary::converters::LittleEndianConverter<double>>(generator);
    ::binary::AddConverter<::binary::converters::LittleEndianConverter<int32_t>>(generator);
    ::binary::AddConverter<::binary::converters::LittleEndianStringConverter<std::string>>(generator);
    ::binary::AddConverter<::binary::converters::ContainerConverter<std::vector<int32_t>>>(generator);
    ::binary::AddConverter<::binary::converters::ContainerConverter<std::vector<std::string>>>(generator);
    return generator;
}

static void EncodePFRTuple(benchmark::State& state) {
    auto generator = GetTestGeneratorWithCommonTypes();
    ::binary::AddConverter<::binary::converters::TupleConverter<Type02>>(generator);
    ::binary::AddConverter<::binary::converters::TupleConverter<Type01>>(generator);
    auto converter = ::binary::GetConverter<Type01>(generator);
    auto data = GetTestDataOfType01();
    auto memory = std::make_unique<std::byte[]>(BufferLength);
    std::span<std::byte> span(memory.get(), BufferLength);

    for (auto _ : state) {
        ::binary::Allocator allocator(span);
        converter->Encode(allocator, data);
    }
}

static void EncodeSTDTuple(benchmark::State& state) {
    auto generator = GetTestGeneratorWithCommonTypes();
    ::binary::AddConverter<::binary::converters::TupleConverter<TypeX2>>(generator);
    ::binary::AddConverter<::binary::converters::TupleConverter<TypeX1>>(generator);
    auto converter = ::binary::GetConverter<TypeX1>(generator);
    auto data = GetTestDataOfTypeX1();
    auto memory = std::make_unique<std::byte[]>(BufferLength);
    std::span<std::byte> span(memory.get(), BufferLength);

    for (auto _ : state) {
        ::binary::Allocator allocator(span);
        converter->Encode(allocator, data);
    }
}

static void EncodeTemplatePFRTuple(benchmark::State& state) {
    auto data = GetTestDataOfType01();
    auto memory = std::make_unique<std::byte[]>(BufferLength);
    std::span<std::byte> span(memory.get(), BufferLength);

    for (auto _ : state) {
        ::binary::Allocator allocator(span);
        Type01TemplateConverter::Encode(allocator, data);
    }
}

static void EncodeTemplateSTDTuple(benchmark::State& state) {
    auto data = GetTestDataOfTypeX1();
    auto memory = std::make_unique<std::byte[]>(BufferLength);
    std::span<std::byte> span(memory.get(), BufferLength);

    for (auto _ : state) {
        ::binary::Allocator allocator(span);
        TypeX1TemplateConverter::Encode(allocator, data);
    }
}

static void DecodePFRTuple(benchmark::State& state) {
    auto generator = GetTestGeneratorWithCommonTypes();
    ::binary::AddConverter<::binary::converters::TupleConverter<Type02>>(generator);
    ::binary::AddConverter<::binary::converters::TupleConverter<Type01>>(generator);
    auto converter = ::binary::GetConverter<Type01>(generator);
    auto data = GetTestDataOfType01();
    ::binary::Allocator allocator;
    converter->Encode(allocator, data);
    const auto span = allocator.AsSpan();

    for (auto _ : state) {
        converter->Decode(span);
    }
}

static void DecodeSTDTuple(benchmark::State& state) {
    auto generator = GetTestGeneratorWithCommonTypes();
    ::binary::AddConverter<::binary::converters::TupleConverter<TypeX2>>(generator);
    ::binary::AddConverter<::binary::converters::TupleConverter<TypeX1>>(generator);
    auto converter = ::binary::GetConverter<TypeX1>(generator);
    auto data = GetTestDataOfTypeX1();
    ::binary::Allocator allocator;
    converter->Encode(allocator, data);
    const auto span = allocator.AsSpan();

    for (auto _ : state) {
        converter->Decode(span);
    }
}

static void DecodeTemplatePFRTuple(benchmark::State& state) {
    auto data = GetTestDataOfType01();
    ::binary::Allocator allocator;
    Type01TemplateConverter::Encode(allocator, data);
    const auto span = allocator.AsSpan();

    for (auto _ : state) {
        Type01TemplateConverter::Decode(span);
    }
}

static void DecodeTemplateSTDTuple(benchmark::State& state) {
    auto data = GetTestDataOfTypeX1();
    ::binary::Allocator allocator;
    TypeX1TemplateConverter::Encode(allocator, data);
    const auto span = allocator.AsSpan();

    for (auto _ : state) {
        TypeX1TemplateConverter::Decode(span);
    }
}

BENCHMARK(EncodePFRTuple)->Name("Encode PFR Tuple");
BENCHMARK(EncodeSTDTuple)->Name("Encode STD Tuple");
BENCHMARK(EncodeTemplatePFRTuple)->Name("Encode Template PFR Tuple");
BENCHMARK(EncodeTemplateSTDTuple)->Name("Encode Template STD Tuple");

BENCHMARK(DecodePFRTuple)->Name("Decode PFR Tuple");
BENCHMARK(DecodeSTDTuple)->Name("Decode STD Tuple");
BENCHMARK(DecodeTemplatePFRTuple)->Name("Decode Template PFR Tuple");
BENCHMARK(DecodeTemplateSTDTuple)->Name("Decode Template STD Tuple");

BENCHMARK_MAIN();
