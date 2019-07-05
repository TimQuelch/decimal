cmake_minimum_required(VERSION 3.10)
project(decimal VERSION 0.1.0 LANGUAGES CXX)

# Include conan files if they exist
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake OPTIONAL)
include(${CMAKE_BINARY_DIR}/conan_paths.cmake OPTIONAL)

# Add library target
add_library(decimal INTERFACE)
add_library(decimal::decimal ALIAS decimal)

# Configure library target
target_include_directories(
    decimal
    INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/>  
    $<INSTALL_INTERFACE:include/>)
target_compile_features(decimal INTERFACE cxx_std_17)

# Add tests
enable_testing()
add_subdirectory(test)

# Install
#include(GNUInstallDirs)
#set(INSTALL_CONFIGDIR ${CMAKE_INSTALL_LIBDIR}/cmake/decimal)
#
#install(
#    TARGETS decimal
#    EXPORT decimal-targets
#    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})
#
#install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
#
#install(
#    EXPORT decimal-targets
#    FILE decimalTargets.cmake
#    NAMESPACE decimal::
#    DESTINATION ${INSTALL_CONFIGDIR})
#
#include(CMakePackageConfigHelpers)
#write_basic_package_version_file(
#    ${CMAKE_CURRENT_BINARY_DIR}/decimalConfigVersion.cmake
#    VERSION ${PROJECT_VERSION}
#    COMPATIBILITY AnyNewerVersion)
#
#configure_package_config_file(
#    ${CMAKE_CURRENT_LIST_DIR}/cmake/decimalConfig.cmake.in
#    ${CMAKE_CURRENT_BINARY_DIR}/decimalConfig.cmake
#    INSTALL_DESTINATION ${INSTALL_CONFIGDIR})
#
#install(
#    FILES
#    ${CMAKE_CURRENT_BINARY_DIR}/decimalConfig.cmake
#    ${CMAKE_CURRENT_BINARY_DIR}/decimalConfigVersion.cmake
#    DESTINATION ${INSTALL_CONFIGDIR})
#
#export(
#    EXPORT decimal-targets
#    FILE ${CMAKE_CURRENT_BINARY_DIR}/decimalTargets.cmake
#    NAMESPACE decimal::)
#
#export(PACKAGE decimal)
