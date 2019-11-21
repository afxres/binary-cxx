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
	"converters_tests/native_converter_tests.cpp")

target_link_libraries (${PROJECT_NAME} ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
