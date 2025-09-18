cmake_minimum_required(VERSION 3.14)
project(Light)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/tools/cmake)

include(CheckCXXSourceCompiles)
include(${CMAKE_DIR}/functions.cmake)
include(${CMAKE_DIR}/definitions.cmake)
include(${CMAKE_DIR}/dependencies.cmake)

add_option(ENABLE_UNIT_TESTS "Enables the building of the unit test modules")
add_option(ENABLE_FUZZ_TESTS "Enables the building of the fuzz test modules")

add_option(ENABLE_STATIC_ANALYSIS "Makes clang-tidy checks mandatory for compilation")
if (ENABLE_STATIC_ANALYSIS)
    set(CMAKE_CXX_CLANG_TIDY "clang-tidy;--warnings-as-errors=*;--allow-no-checks")
endif ()

add_option(ENABLE_LLVM_COVERAGE "Enables the code coverage instrumentation for clang")
if(ENABLE_LLVM_COVERAGE)
    if (NOT "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
        message(FATAL_ERROR "ENABLE_LLVM_COVERAGE only supports the clang compiler")
    endif ()

    # Check for libc++
    check_cxx_source_compiles("
        #include <string>
        #ifdef _LIBCPP_VERSION
        int main() { return 0; }
        #else
        #error Not using libc++
        #endif
    " USING_LIBCXX)
    if(NOT USING_LIBCXX)
        message(FATAL_ERROR "ENABLE_LLVM_COVERAGE requires libc++, please compile with -stdlib=libc++")
    endif()

    add_compile_options(-fprofile-instr-generate -fcoverage-mapping)
    add_link_options(-fprofile-instr-generate -fcoverage-mapping)
endif ()

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/modules)
