import os

from conans import ConanFile, CMake, tools

class DecicmalTestConan(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    exports_sources = ("*", "!build")
    generators = "cmake_paths"

    def _configure_cmake(self):
        cmake = CMake(self)
        cmake.configure()
        return cmake

    def build(self):
        cmake = self._configure_cmake()
        cmake.build()

    def test(self):
        cmake = self._configure_cmake()
        cmake.test()
