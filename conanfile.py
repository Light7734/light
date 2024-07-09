from conan import ConanFile
from conan.tools.cmake import CMakeToolchain

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

    def generate(self):
        tc = CMakeToolchain(self)

        tc.cache_variables["CMAKE_EXPORT_COMPILE_COMMANDS"] = True
        tc.cache_variables["ENABLE_SANITIZERS"] = self.options.enable_sanitizers
        tc.cache_variables["ENABLE_STATIC_ANALYSIS"] = self.options.enable_static_analysis

        tc.generate()
