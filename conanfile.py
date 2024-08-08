from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMake, cmake_layout
import shutil
import os

class LightRecipe(ConanFile):
    name = "light"

    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps"

    requires = [
        "benchmark/1.8.4",
        "gtest/1.14.0",
    ]

    tool_requires = [
       "cmake/3.30.0"
    ]

    options = {
        "enable_static_analysis": [True, False],
        "enable_sanitizers": [True, False],
    }

    default_options = {
        "enable_static_analysis": True,
        "enable_sanitizers": False,
    }

    def layout(self):
        cmake_layout(self)

    def generate(self):
        tc = CMakeToolchain(self)

        tc.cache_variables["CMAKE_EXPORT_COMPILE_COMMANDS"] = True
        tc.cache_variables["ENABLE_SANITIZERS"] = self.options.enable_sanitizers
        tc.cache_variables["ENABLE_STATIC_ANALYSIS"] = self.options.enable_static_analysis

        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
        self.copy_compile_commands()

    def copy_compile_commands(self):
        build_folder = self.build_folder
        source_file = os.path.join(build_folder, "compile_commands.json")
        destination_file = os.path.join(self.source_folder, "compile_commands.json")

        if os.path.isfile(source_file):
            shutil.copy(source_file, destination_file)
            self.output.info(f"Copied compile_commands.json to {destination_file}")
        else:
            self.output.warn("compile_commands.json not found!")
