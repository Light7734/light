set(CMAKE_CXX_STANDARD 26)
set(CMAKE_EPXORT_COMPILE_COMMANDS TRUE)
set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "f35a9ac6-8463-4d38-8eec-5d6008153e7d")
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_MODULE_STD 1)

cmake_minimum_required(VERSION 4.1)
project(Light)

include(${CMAKE_CURRENT_SOURCE_DIR}/tools/cmake/module.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/tools/cmake/definitions.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/tools/cmake/options.cmake)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/modules)
