from conans import ConanFile, tools, CMake

class SeqslamBenchmarkConan(ConanFile):
    generators = ("cmake_paths")

    def build_requirements(self):
        if tools.get_env("CONAN_RUN_TESTS", True):
            self.build_requires("Catch2/2.7.1@catchorg/stable")

    def _configure_cmake(self):
        cmake = CMake(self)
        cmake.definitions["DECIMAL_ENABLE_TESTING"] = "ON" if tools.get_env("CONAN_RUN_TESTS", True) else "OFF"
        cmake.configure()
        return cmake

    def build(self):
        cmake = _configure_cmake(self)
        cmake.build()
        if tools.get_env("CONAN_RUN_TESTS", True):
            cmake.test()

    def package(self):
        cmake = self._configure_cmake()
        cmake.install()

