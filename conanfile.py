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
    }

    default_options = {
    }

    def requirements(self):
        self.requires("gtest/1.16.0")
        self.requires("entt/3.15.0")
        self.requires("glfw/3.4")
        self.requires("glm/1.0.1")
        self.requires("spdlog/1.15.3")
        self.requires("spirv-cross/1.4.313.0")
        self.requires("stb/cci.20240531")
        self.requires("volk/1.3.296.0")
        self.requires("yaml-cpp/0.8.0")

    def layout(self):
        cmake_layout(self)

    def generate(self):
        tc = CMakeToolchain(self)

        tc.variables["CMAKE_BUILD_TYPE"] = self.settings.build_type
        tc.cache_variables["CMAKE_EXPORT_COMPILE_COMMANDS"] = True

        repo = git.Repo(search_parent_directories=True)
        tc.cache_variables["GIT_HASH"] = repo.head.object.hexsha

        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
