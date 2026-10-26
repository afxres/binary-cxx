#ifndef BINARY_BENCHMARKS_INTEGRATION_TESTS_COMMON_HPP
#define BINARY_BENCHMARKS_INTEGRATION_TESTS_COMMON_HPP

#include <cstddef>
#include <cstdint>
#include <string>
#include <tuple>
#include <vector>

#include <binary/Generator.hpp>
#include <binary/components/MemberDescriptor.hpp>

inline constexpr std::size_t BufferLength = 1024;

using TypeX2 = std::tuple<double, std::vector<std::string>>;
using TypeX1 = std::tuple<int32_t, std::string, std::vector<int32_t>, TypeX2>;

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

TypeX1 GetTestDataOfTypeX1();
Type01 GetTestDataOfType01();

::binary::Generator GetTestGeneratorWithCommonTypes();

#endif
