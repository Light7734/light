from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMake, cmake_layout
import shutil
import os
import git

class LightRecipe(ConanFile):
    name = "Light Engine"

    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps"

    options = {
        "enable_unit_tests": [True, False],
        "enable_fuzz_tests": [True, False],
        "enable_llvm_coverage": [True, False],
        "enable_static_analysis": [True, False],
        "use_mold": [True, False],
        "export_compile_commands": [True, False],
    }

    default_options = {
        "enable_unit_tests": True,
        "enable_fuzz_tests": False,
        "enable_llvm_coverage": False,
        "enable_static_analysis": False,
        "use_mold": False,
        "export_compile_commands": True,
    }

    def requirements(self):
        self.requires("entt/3.15.0")
        self.requires("stb/cci.20240531")
        self.requires("yaml-cpp/0.8.0")
        self.requires("lz4/1.10.0")

    def layout(self):
        cmake_layout(self)

    def generate(self):
        tc = CMakeToolchain(self)

        tc.variables["CMAKE_BUILD_TYPE"] = self.settings.build_type

        if self.options.use_mold:
            tc.cache_variables["CMAKE_LINKER_TYPE"] = "MOLD"

        tc.cache_variables["CMAKE_EXPORT_COMPILE_COMMANDS"] = self.options.export_compile_commands
        tc.cache_variables["ENABLE_UNIT_TESTS"] = self.options.enable_unit_tests
        tc.cache_variables["ENABLE_FUZZ_TESTS"] = self.options.enable_fuzz_tests
        tc.cache_variables["ENABLE_LLVM_COVERAGE"] = self.options.enable_llvm_coverage
        tc.cache_variables["ENABLE_STATIC_ANALYSIS"] = self.options.enable_static_analysis

        repo = git.Repo(search_parent_directories=True)
        tc.cache_variables["GIT_HASH"] = repo.head.object.hexsha

        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
