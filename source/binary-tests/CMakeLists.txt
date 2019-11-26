cmake_minimum_required (VERSION 3.8)

set (CMAKE_CXX_STANDARD 17)

project ("binary-tests")

find_package (Boost REQUIRED COMPONENTS unit_test_framework)

include_directories(
	${Boost_INCLUDE_DIRS}
	"../binary/include/")

add_executable (
	${PROJECT_NAME}
	"main.cpp"
	"binary/converters/containers/container_converter_integration_tests.cpp"
	"binary/converters/native_converter_tests.cpp"
	"binary/converters/pair_converter_tests.cpp"
	"binary/converters/string_converter_tests.cpp"
	"binary/converters/tuple_converter_tests.cpp"
	"binary/implementations/simple_allocator_tests.cpp"
	"binary/implementations/simple_span_view_tests.cpp"
	"binary/primitive_helper_tests.cpp")

target_link_libraries (${PROJECT_NAME} ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
