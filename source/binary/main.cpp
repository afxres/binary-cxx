#include "include/span_view.hpp"
#include "include/allocator_helper.hpp"
#include "include/primitive_helper.hpp"
#include "include/converters/native_converter.hpp"
#include "include/converters/string_converter.hpp"
#include "include/converters/tuple_converter.hpp"
#include "include/implementations/simple_allocator.hpp"

#include <iostream>
#include <array>

namespace mk = mikodev::binary;
namespace mkc = mikodev::binary::converters;
namespace mki = mikodev::binary::implementations;

void number_test(size_t number)
{
    auto allocator = mki::simple_allocator();
    mk::primitive_helper::encode_number(allocator, number);
    auto dump = allocator.dump();
    auto view = dump.as_span_view();
    auto result = mk::primitive_helper::decode_number(view);
    std::cout << "number: " << number << ", result: " << result << ", allocator size: " << dump.size() << std::endl;
}

void anchor_test()
{
    auto allocator = mki::simple_allocator();
    auto anchor = mk::allocator_helper::anchor_length_prefix(allocator);
    mk::allocator_helper::append_length_prefix(allocator, anchor);
    auto dump = allocator.dump();
    auto view = dump.as_span_view();
    auto result = mk::primitive_helper::decode_number(view);
    std::cout << "result: " << result << ", allocator size: " << dump.size() << std::endl;
}

void converter_test(int32_t item)
{
    auto allocator = mki::simple_allocator();
    auto converter = mkc::native_converter<std::int32_t>();
    converter.encode_with_length_prefix(allocator, item);
    auto dump = allocator.dump();
    auto view = dump.as_span_view();
    auto result = converter.decode_with_length_prefix(view);
    std::cout << "source :" << item << ", result: " << result << ", size: " << allocator.size() << ", capacity: " << allocator.capacity() << std::endl;
}

void string_converter_test(const std::string& text)
{
    auto converter = mkc::string_converter();
    auto allocator = mki::simple_allocator();
    converter.encode_with_length_prefix(allocator, text);
    auto dump = allocator.dump();
    auto view = dump.as_span_view();
    auto result = converter.decode_with_length_prefix(view);
    std::cout << "source :" << text << ", result: " << result << ", size: " << allocator.size() << ", capacity: " << allocator.capacity() << std::endl;
}

void tuple_converter_test()
{
    auto converter = mkc::tuple_converter<int32_t, int64_t>(
        std::make_shared<mkc::native_converter<int32_t>>(),
        std::make_shared<mkc::native_converter<int64_t>>());
    auto allocator = mki::simple_allocator();
    converter.encode(allocator, std::make_tuple(1, 2));
    auto dump = allocator.dump();
    std::cout << "buffer: " << dump.size() << std::endl;
}

int main()
{
    converter_test(1024);
    converter_test(123456789);

    string_converter_test("Abcd");
    string_converter_test("0123456789");

    tuple_converter_test();

    anchor_test();

    number_test(0);
    number_test(1);
    number_test(63);
    number_test(64);
    number_test(1024);
    number_test(16383);
    number_test(16384);
    number_test(65536);
    return 0;
}
