from conans import ConanFile

class SeqslamBenchmarkConan(ConanFile):
    requires = ("Catch2/2.7.1@catchorg/stable")
    generators = ("cmake_paths")
