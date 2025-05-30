#include <benchmark/benchmark.h>

#include <cstddef>
#include <sstream>
#include <string>
#include <tuple>

#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/vector.hpp>

#include <binary/Allocator.hpp>
#include <binary/Generator.hpp>
#include <binary/GeneratorExtensions.hpp>
#include <binary/components/NamedObject.hpp>
#include <binary/components/TupleObject.hpp>
#include <binary/converters/ContainerConverter.hpp>
#include <binary/converters/LittleEndianConverter.hpp>
#include <binary/converters/LittleEndianStringConverter.hpp>
#include <binary/converters/TupleConverter.hpp>

struct Type02 {
    double Data;
    std::vector<std::string> Tags;
};

struct Type01 {
    int32_t Id;
    std::string Name;
    std::vector<int32_t> List;
    Type02 Item;
};

using TypeX2 = std::tuple<double, std::vector<std::string>>;
using TypeX1 = std::tuple<int32_t, std::string, std::vector<int32_t>, TypeX2>;

BINARY_NAMED_OBJECT_CONVERTER(Type02NamedObjectConverter, Type02) {
    BINARY_NAMED_MEMBER(Data);
    BINARY_NAMED_MEMBER(Tags);
}

BINARY_NAMED_OBJECT_CONVERTER(Type01NamedObjectConverter, Type01) {
    BINARY_NAMED_MEMBER(Id);
    BINARY_NAMED_MEMBER(Name);
    BINARY_NAMED_MEMBER(List);
    BINARY_NAMED_MEMBER(Item);
}

BINARY_TUPLE_OBJECT_CONVERTER(Type02TupleObjectConverter, Type02) {
    BINARY_TUPLE_MEMBER(Data);
    BINARY_TUPLE_MEMBER(Tags);
}

BINARY_TUPLE_OBJECT_CONVERTER(Type01TupleObjectConverter, Type01) {
    BINARY_TUPLE_MEMBER(Id);
    BINARY_TUPLE_MEMBER(Name);
    BINARY_TUPLE_MEMBER(List);
    BINARY_TUPLE_MEMBER(Item);
}

template <typename Archive>
void serialize(Archive& archive, Type02& item, [[maybe_unused]] const unsigned int version) {
    archive & item.Data & item.Tags;
}

template <typename Archive>
void serialize(Archive& archive, Type01& item, [[maybe_unused]] const unsigned int version) {
    archive & item.Id & item.Name & item.List & item.Item;
}

static ::binary::Generator GetTestGeneratorWithCommonTypes() {
    ::binary::Generator generator;
    ::binary::AddConverter<::binary::converters::LittleEndianConverter<double>>(generator);
    ::binary::AddConverter<::binary::converters::LittleEndianConverter<int32_t>>(generator);
    ::binary::AddConverter<::binary::converters::LittleEndianStringConverter<std::string>>(generator);
    ::binary::AddConverter<::binary::converters::ContainerConverter<std::vector<int32_t>>>(generator);
    ::binary::AddConverter<::binary::converters::ContainerConverter<std::vector<std::string>>>(generator);
    return generator;
}

static Type01 GetTestDataOfType01() {
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

static TypeX1 GetTestDataOfTypeX1() {
    TypeX2 item = {2.2, {"one", "two", "three"}};
    TypeX1 data = {1024, "csharp", {7, 11, 555, 1313}, item};
    return data;
}

static void EncodeNamedObject(benchmark::State& state) {
    auto generator = GetTestGeneratorWithCommonTypes();
    ::binary::AddConverter<Type02NamedObjectConverter>(generator);
    ::binary::AddConverter<Type01NamedObjectConverter>(generator);
    auto converter = ::binary::GetConverter<Type01>(generator);
    auto data = GetTestDataOfType01();
    auto length = static_cast<size_t>(state.range(0));
    auto memory = std::make_unique<std::byte[]>(length);
    std::span<std::byte> span(memory.get(), length);

    for (auto _ : state) {
        ::binary::Allocator allocator(span);
        converter->Encode(allocator, data);
    }
}

static void EncodeTupleObject(benchmark::State& state) {
    auto generator = GetTestGeneratorWithCommonTypes();
    ::binary::AddConverter<Type02TupleObjectConverter>(generator);
    ::binary::AddConverter<Type01TupleObjectConverter>(generator);
    auto converter = ::binary::GetConverter<Type01>(generator);
    auto data = GetTestDataOfType01();
    auto length = static_cast<size_t>(state.range(0));
    auto memory = std::make_unique<std::byte[]>(length);
    std::span<std::byte> span(memory.get(), length);

    for (auto _ : state) {
        ::binary::Allocator allocator(span);
        converter->Encode(allocator, data);
    }
}

static void EncodeSystemTuple(benchmark::State& state) {
    auto generator = GetTestGeneratorWithCommonTypes();
    ::binary::AddConverter<::binary::converters::TupleConverter<TypeX2>>(generator);
    ::binary::AddConverter<::binary::converters::TupleConverter<TypeX1>>(generator);
    auto converter = ::binary::GetConverter<TypeX1>(generator);
    auto data = GetTestDataOfTypeX1();
    auto length = static_cast<size_t>(state.range(0));
    auto memory = std::make_unique<std::byte[]>(length);
    std::span<std::byte> span(memory.get(), length);

    for (auto _ : state) {
        ::binary::Allocator allocator(span);
        converter->Encode(allocator, data);
    }
}

static void DecodeNamedObject(benchmark::State& state) {
    auto generator = GetTestGeneratorWithCommonTypes();
    ::binary::AddConverter<Type02NamedObjectConverter>(generator);
    ::binary::AddConverter<Type01NamedObjectConverter>(generator);
    auto converter = ::binary::GetConverter<Type01>(generator);
    auto data = GetTestDataOfType01();
    ::binary::Allocator allocator;
    converter->Encode(allocator, data);
    const auto span = allocator.AsSpan();

    for (auto _ : state) {
        converter->Decode(span);
    }
}

static void DecodeTupleObject(benchmark::State& state) {
    auto generator = GetTestGeneratorWithCommonTypes();
    ::binary::AddConverter<Type02TupleObjectConverter>(generator);
    ::binary::AddConverter<Type01TupleObjectConverter>(generator);
    auto converter = ::binary::GetConverter<Type01>(generator);
    auto data = GetTestDataOfType01();
    ::binary::Allocator allocator;
    converter->Encode(allocator, data);
    const auto span = allocator.AsSpan();

    for (auto _ : state) {
        converter->Decode(span);
    }
}

static void DecodeSystemTuple(benchmark::State& state) {
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

static void BoostEncodeTupleObjectText(benchmark::State& state) {
    auto data = GetTestDataOfType01();

    for (auto _ : state) {
        std::stringstream stream;
        boost::archive::text_oarchive target(stream);
        target << data;
    }
}

static void BoostEncodeTupleObjectTextReuseStream(benchmark::State& state) {
    auto data = GetTestDataOfType01();
    std::stringstream stream;

    for (auto _ : state) {
        stream.clear();
        stream.str({});
        boost::archive::text_oarchive target(stream);
        target << data;
    }
}

static void BoostEncodeTupleObjectBinary(benchmark::State& state) {
    auto data = GetTestDataOfType01();

    for (auto _ : state) {
        std::stringstream stream;
        boost::archive::binary_oarchive target(stream);
        target << data;
    }
}

static void BoostEncodeTupleObjectBinaryReuseStream(benchmark::State& state) {
    auto data = GetTestDataOfType01();
    std::stringstream stream;

    for (auto _ : state) {
        stream.clear();
        stream.str({});
        boost::archive::binary_oarchive target(stream);
        target << data;
    }
}

static void BoostDecodeTupleObjectText(benchmark::State& state) {
    auto data = GetTestDataOfType01();
    std::stringstream stream;
    boost::archive::text_oarchive target(stream);
    target << data;

    for (auto _ : state) {
        stream.seekg(0, std::ios::beg);
        ::boost::archive::text_iarchive source(stream);
        decltype(data) result;
        source >> result;
    }
}

static void BoostDecodeTupleObjectBinary(benchmark::State& state) {
    auto data = GetTestDataOfType01();
    std::stringstream stream;
    boost::archive::binary_oarchive target(stream);
    target << data;

    for (auto _ : state) {
        stream.seekg(0, std::ios::beg);
        ::boost::archive::binary_iarchive source(stream);
        decltype(data) result;
        source >> result;
    }
}

BENCHMARK(EncodeNamedObject)->Name("Encode Custom Named Object, pre-allocate memory")->Arg(0)->Arg(1024);
BENCHMARK(EncodeTupleObject)->Name("Encode Custom Tuple Object, pre-allocate memory")->Arg(0)->Arg(1024);
BENCHMARK(EncodeSystemTuple)->Name("Encode System Tuple, pre-allocate memory")->Arg(0)->Arg(1024);

BENCHMARK(DecodeNamedObject)->Name("Decode Custom Named Object");
BENCHMARK(DecodeTupleObject)->Name("Decode Custom Tuple Object");
BENCHMARK(DecodeSystemTuple)->Name("Decode System Tuple");

BENCHMARK(BoostEncodeTupleObjectText)->Name("Boost Encode Custom Tuple Object (text)");
BENCHMARK(BoostEncodeTupleObjectTextReuseStream)->Name("Boost Encode Custom Tuple Object (text, reuse stream)");
BENCHMARK(BoostEncodeTupleObjectBinary)->Name("Boost Encode Custom Tuple Object (binary)");
BENCHMARK(BoostEncodeTupleObjectBinaryReuseStream)->Name("Boost Encode Custom Tuple Object (binary, reuse stream)");

BENCHMARK(BoostDecodeTupleObjectText)->Name("Boost Decode Custom Tuple Object (text)");
BENCHMARK(BoostDecodeTupleObjectBinary)->Name("Boost Decode Custom Tuple Object (binary)");

BENCHMARK_MAIN();
