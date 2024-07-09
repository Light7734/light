cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
project("light" LANGUAGES CXX)

include(tools/cmake/preliminary.cmake)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_option(ENABLE_SANITIZERS "Enables fsan sanitizers")
add_option(ENABLE_STATIC_ANALYSIS "Enables clang-tidy static analysis")

find_package(benchmark REQUIRED)
find_package(GTest REQUIRED)

if(ENABLE_STATIC_ANALYSIS)
    find_program(CLANG_TIDY_EXE NAMES "clang-tidy" REQUIRED)
endif()

add_subdirectory(docs)
add_subdirectory(modules)
