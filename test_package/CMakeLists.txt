cmake_minimum_required(VERSION 2.8.12)
project(decimal-test LANGUAGES CXX)

include(${CMAKE_BINARY_DIR}/conan_paths.cmake OPTIONAL)

find_package(decimal REQUIRED)

add_executable(test-consumer test-consumer.cpp)
target_link_libraries(test-consumer decimal::decimal)

enable_testing()
add_test(NAME test-consumer COMMAND test-consumer)
