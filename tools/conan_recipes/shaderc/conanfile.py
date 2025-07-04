import os

from conan import ConanFile
from conan.tools.build import check_min_cppstd, stdcpp_library
from conan.tools.cmake import CMake, CMakeDeps, CMakeToolchain, cmake_layout
from conan.tools.env import VirtualBuildEnv
from conan.tools.files import apply_conandata_patches, copy, export_conandata_patches, get, rmdir
from conan.tools.microsoft import is_msvc, is_msvc_static_runtime
from conan.tools.apple import fix_apple_shared_install_name

required_conan_version = ">=2.10.0"


class ShadercConan(ConanFile):
    name = "shaderc"
    version = "2025.3"
    description = "A collection of tools, libraries and tests for shader compilation."
    license = "Apache-2.0"
    url = "https://github.com/conan-io/conan-center-index"
    homepage = "https://github.com/google/shaderc"
    topics = ("glsl", "hlsl", "msl", "spirv", "spir-v", "glslc")

    package_type = "library"
    settings = "os", "arch", "compiler", "build_type"
    options = {
        "shared": [True, False],
        "fPIC": [True, False],
    }
    default_options = {
        "shared": False,
        "fPIC": True,
    }

    def configure(self):
        if self.options.shared:
            self.options.rm_safe("fPIC")

    def layout(self):
        cmake_layout(self, src_folder="src")

    def requirements(self):
        self.requires("glslang/1.4.313.0")
        self.requires("spirv-tools/1.4.313.0")
        self.requires("spirv-headers/1.4.313.0")

    def validate(self):
        if self.settings.compiler.get_safe("cppstd"):
            check_min_cppstd(self, 11)

    def build_requirements(self):
        self.tool_requires("cmake/[>=3.17.2 <4]")

    def source(self):
        get(self, "https://github.com/google/shaderc/archive/refs/tags/v2025.3.tar.gz", strip_root=True)
        os.system("./utils/git-sync-deps")
        

    def generate(self):
        venv = VirtualBuildEnv(self)
        venv.generate()

        tc = CMakeToolchain(self)
        tc.cache_variables["SHADERC_SKIP_INSTALL"] = False
        tc.cache_variables["SHADERC_SKIP_EXAMPLES"] = True
        tc.cache_variables["SHADERC_SKIP_TESTS"] = True
        tc.cache_variables["ENABLE_CODE_COVERAGE"] = False
        tc.cache_variables["SHADERC_ENABLE_WERROR_COMPILE"] = False
        if is_msvc(self):
            tc.cache_variables["SHADERC_ENABLE_SHARED_CRT"] = not is_msvc_static_runtime(self)
        tc.generate()

        self.dependencies["glslang"].cpp_info.components["glslang-core"].includedirs.append(
            os.path.join(self.dependencies["glslang"].package_folder, "include", "glslang")
        )

        deps = CMakeDeps(self)
        deps.set_property("glslang::glslang-core", "cmake_target_name", "glslang")
        deps.set_property("glslang::osdependent", "cmake_target_name", "OSDependent")
        deps.set_property("glslang::spirv", "cmake_target_name", "SPIRV")
        deps.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        copy(self, "LICENSE", dst=os.path.join(self.package_folder, "licenses"), src=self.source_folder)
        cmake = CMake(self)
        cmake.install()
        fix_apple_shared_install_name(self)
        rmdir(self, os.path.join(self.package_folder, "lib", "pkgconfig"))

    def package_info(self):
        if self.options.shared:
            self.cpp_info.set_property("pkg_config_name", "shaderc")
            self.cpp_info.libs = ["shaderc_shared"]
            self.cpp_info.defines.append("SHADERC_SHAREDLIB")
        else:
            self.cpp_info.set_property("pkg_config_name", "shaderc_static")
            self.cpp_info.libs = ["shaderc", "shaderc_util"]
            if stdcpp_library(self):
                self.cpp_info.system_libs.append(stdcpp_library(self))

        if self.settings.os in ["Linux", "FreeBSD"]:
            self.cpp_info.system_libs.append("pthread")

        self.cpp_info.requires = [
            "glslang::glslang-core",
            "glslang::osdependent",
            "glslang::spirv",
            "spirv-tools::spirv-tools-core",
            "spirv-tools::spirv-tools-opt",
            "spirv-headers::spirv-headers"
        ]

        # TODO: to remove in conan v2
        bin_path = os.path.join(self.package_folder, "bin")
        self.env_info.PATH.append(bin_path)
