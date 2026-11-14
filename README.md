# Binary (C++)

[![GitHub repo size](https://img.shields.io/github/repo-size/afxres/binary-cxx)](#)
[![GitHub Workflow Status](https://img.shields.io/github/actions/workflow/status/afxres/binary-cxx/build.yml?branch=main)](#)
[![Coverage Status](https://coveralls.io/repos/github/afxres/binary-cxx/badge.svg?branch=main)](https://coveralls.io/github/afxres/binary-cxx?branch=main)

## Overview

C++20 serialization library. It shares its binary layout with the
[C# version](https://github.com/afxres/binary): the same length prefix and the same named object
structure, so data written by one can be read by the other when the member names and types match.

Two APIs work on that single format:

- **virtual** — converters are objects. They are registered into a `binary::Generator` and looked up
  by `std::type_index` at run time.
- **template** — converters are resolved at compile time by `binary::experimental::Converter<T>`.
  There is no registry.

## Getting Started

Requires C++20. The virtual API has no external dependency. The template API needs Boost (PFR), and
the tests additionally need Boost.Test.

```cmake
add_subdirectory(subdirectory/to/binary-cxx/code)      # path to this repository
target_link_libraries(app PRIVATE binary-experimental) # template + virtual
# target_link_libraries(app PRIVATE binary)            # virtual only
```

## Data Model

Both APIs use the same model. Only named objects need a schema.

```cpp
#include <cstdint>
#include <string>
#include <tuple>

#include <binary/components/MemberDescriptor.hpp>

struct Person {
    std::int32_t Id;
    std::string Name;
};

struct PersonSchema {
    static constexpr auto Members = std::tuple{
        binary::components::NamedMember{"Id", &Person::Id},
        binary::components::NamedMember{"Name", &Person::Name},
    };
};
```

## Virtual API

```cpp
#include <binary/Allocator.hpp>
#include <binary/Generator.hpp>
#include <binary/GeneratorExtensions.hpp>
#include <binary/components/NamedObjectConverter.hpp>
#include <binary/converters/LittleEndianConverter.hpp>
#include <binary/converters/LittleEndianStringConverter.hpp>

void VirtualExample() {
    binary::Generator generator;
    binary::AddConverter<binary::converters::LittleEndianConverter<std::int32_t>>(generator);
    binary::AddConverter<binary::converters::LittleEndianStringConverter<std::string>>(generator);
    binary::AddConverter<binary::components::NamedObjectConverter<Person, PersonSchema>>(generator);

    auto converter = binary::GetConverter<Person>(generator);
    Person source{1024, "C++"};

    binary::Allocator allocator;
    converter->Encode(allocator, source);

    const auto bytes = allocator.AsSpan();
    Person result = converter->Decode(bytes);
}
```

`binary::Allocator` owns its buffer. Passing a span (`binary::Allocator allocator(span);`) makes it
write into caller memory instead, which is useful for fixed size buffers. Use
`EncodeWithLengthPrefix` / `DecodeWithLengthPrefix` when the payload is embedded into a larger
stream.

## Template API

```cpp
#include <binary/Allocator.hpp>
#include <binary/experimental/Converter.hpp>

// The schema is found with ADL, so it must be declared in the namespace of Person
// before the first use of Converter<Person>.
PersonSchema GetNamedObjectSchema(Person*);

void TemplateExample() {
    Person source{1024, "C++"};

    binary::Allocator allocator;
    binary::experimental::Converter<Person>::Encode(allocator, source);
    Person result = binary::experimental::Converter<Person>::Decode(allocator.AsSpan());

    // Same call, but the bytes are allocated into a std::vector<std::byte>.
    auto bytes = binary::experimental::Encode(source);
    Person other = binary::experimental::Decode<Person>(bytes);
}
```

## Which API?

|             | virtual                                           | template                                                          |
| :---------- | :------------------------------------------------ | :---------------------------------------------------------------- |
| Type set    | assembled at run time                             | fixed at compile time                                             |
| Setup       | `Generator` + `AddConverter`                      | none, schema via ADL                                              |
| Dispatch    | virtual call through `IConverter`                 | static call, inlinable                                            |
| Custom type | subclass `binary::Converter<T>`, then register it | specialize `binary::experimental::helpers::GetConverterHelper<T>` |
| Dependency  | `binary`                                          | `binary-experimental` (+ Boost.PFR)                               |

Both APIs write the same bytes, so the choice is about assembling types, not about compatibility.
Prefer the template API when the type set is known at compile time; prefer the virtual API when
converters must be created, shared or injected at run time.

## Supported Types

| Type                                                             | Converter                                                                      |
| :--------------------------------------------------------------- | :----------------------------------------------------------------------------- |
| Arithmetic types, enums                                          | `LittleEndianConverter<T>`                                                     |
| `std::string`, `std::u16string`, `std::u32string`                | `LittleEndianStringConverter<T>`                                               |
| Ranges (`std::vector`, `std::list`, `std::set`, `std::map`, ...) | `ContainerConverter<T>`                                                        |
| `std::tuple`                                                     | `TupleConverter<T>`                                                            |
| Aggregate structs                                                | `NamedObjectConverter<T, Schema>` (named), or `TupleConverter<T>` (positional) |
| `std::variant`                                                   | `VariantConverter<T>`                                                          |

The virtual API registers each converter explicitly; the template API derives them from the type
automatically. A few details are worth knowing:

- Positional aggregate conversion relies on Boost.PFR, which is included by `binary-experimental`,
  even when only the virtual API is otherwise used.
- Containers are decoded with `emplace` or `emplace_back`, so the container must be resizable;
  fixed size containers such as `std::array` are not supported for decoding.
- Strings are written as little-endian code units without transcoding. `std::string` is stored as
  its bytes (normally UTF-8), `std::u16string` as UTF-16LE, which only matches the C# UTF-8 wire
  format for ASCII.
- Decoding truncated input throws `std::length_error`; a missing converter in a `Generator` throws
  `std::invalid_argument`.
- `std::monostate` is the empty union case. Inside a `std::variant` it writes the tag and nothing
  else, for `Encode` and `EncodeAuto` alike, and the tag alone delimits it, so it needs no
  converter. It has no converter of its own: elsewhere it is a compile error in the template API
  and a missing converter in the virtual API.

## Wire Format

### Length Prefix

| Value                | Leading Bit | Bytes                       | Example              |
| :------------------- | :---------- | :-------------------------- | :------------------- |
| `0 ~ 0x7F`           | `0`         | 1                           | `7F` → 127           |
| `0x80 ~ 0x7FFF'FFFF` | `1`         | 4, big-endian, high bit set | `80 00 04 01` → 1025 |

### Named Object

`Person{1024, "C++"}` (17 bytes):

| Bytes            | Meaning                                       |
| :--------------- | :-------------------------------------------- |
| `02 49 64`       | key `"Id"`, length 2                          |
| `04 00 04 00 00` | value `1024`, length 4, little-endian `int32` |
| `04 4e 61 6d 65` | key `"Name"`, length 4                        |
| `03 43 2b 2b`    | value `"C++"`, length 3                       |

Both the key and the value carry a length prefix, and the object itself has no additional header.
Members are written in the order declared by the schema, but the format does not require any
order: decoding looks members up by name.

### Nested Tuple

```cpp
using Time  = std::tuple<std::int64_t, std::int32_t>;  // Seconds, Nanos
using User  = std::tuple<std::string, std::int32_t>;   // Name, Id
using Event = std::tuple<Time, User, std::string>;     // Time, User, Action

Event value{{1712, 500}, {"amy", 7}, "login"};
```

| Bytes                     | Meaning                                  |
| :------------------------ | :--------------------------------------- |
| `b0 06 00 00 00 00 00 00` | `Time.Seconds = 1712`                    |
| `f4 01 00 00`             | `Time.Nanos = 500`                       |
| `03 61 6d 79`             | `User.Name = "amy"`, length 3            |
| `07 00 00 00`             | `User.Id = 7`                            |
| `6c 6f 67 69 6e`          | `Action`, last element, no length prefix |

Tuples are flattened on the wire. `Event` above and the flat
`std::tuple<std::int64_t, std::int32_t, std::string, std::int32_t, std::string>` produce the same 25
bytes, and either type decodes a payload written by the other, so fields can be regrouped without
breaking existing data. Nesting adds no headers and no extra bytes: the fields of `Time` are 12
bytes in the stream with nothing wrapping them, and even `std::tuple<std::tuple<std::int32_t>>` is
four bytes.

## Testing

A Debug configure enables the tests, so the build type matters:

```bash
bash scripts/test-multiarch.sh                       # host architecture
```

`test-multiarch.sh` builds and runs the same suite on one or more targets, each in
`build-tests-<arch>/`, and prints one row per target:

```bash
bash scripts/test-multiarch.sh x86_64 aarch64 armhf s390x
```

| target  | bits | endian | tests    | status |
| :------ | :--- | :----- | :------- | :----- |
| x86_64  | 64   | little | 2 passed | ok     |
| aarch64 | 64   | little | 2 passed | ok     |
| armhf   | 32   | little | 2 passed | ok     |
| s390x   | 64   | big    | 2 passed | ok     |

Cross targets run under `qemu-user` with their own sysroot, so no `binfmt_misc` setup is needed.
`--all` adds every supported target and skips the ones whose toolchain is not installed,
`--allow-missing` turns a missing toolchain into a skip instead of a failure, and `--clean`
reconfigures from scratch. The width and endianness of the produced binaries are read back from
their ELF header, so a mislabelled target cannot pass silently.

The scripts themselves are checked by `bash scripts/check-shell.sh`: `bash -n` for syntax,
`shfmt -d` for formatting (the style lives in `.editorconfig`, shared with editors) and
`shellcheck -S warning` for lint. `--fix` rewrites the files in place.

## License

[MIT](LICENSE)
