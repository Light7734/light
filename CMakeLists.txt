cmake_minimum_required(VERSION 3.14)
project(Light)
set(CMAKE_CXX_STANDARD 23)

include(${CMAKE_CURRENT_SOURCE_DIR}/tools/cmake/functions.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/tools/cmake/definitions.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/tools/cmake/dependencies.cmake)

add_option(ENABLE_STATIC_ANALYSIS "Performs static analysis via clang-tidy and fails build on failing checks")
if (ENABLE_STATIC_ANALYSIS)
    set(CMAKE_CXX_CLANG_TIDY "clang-tidy;--warnings-as-errors=*;--allow-no-checks")
endif ()

add_option(ENABLE_TESTS "Enables the building of the test modules")
add_subdirectory(./modules)
add_subdirectory(./external)
