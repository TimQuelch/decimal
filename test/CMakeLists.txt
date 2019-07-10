cmake_minimum_required(VERSION 3.10)
project(decimal)

include(${CMAKE_BINARY_DIR}/conan_paths.cmake OPTIONAL)

find_package(Catch2 REQUIRED)
include(Catch)

add_library(test-main OBJECT test-main.cpp)
target_link_libraries(test-main PUBLIC Catch2::Catch2)

add_executable(tests-decimal tests.cpp)
target_link_libraries(tests-decimal PRIVATE decimal test-main)
catch_discover_tests(tests-decimal)
