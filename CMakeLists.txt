set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EPXORT_COMPILE_COMMANDS TRUE)
set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "d0edc3af-4c50-42ea-a356-e2862fe7a444")
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_MODULE_STD 1)

cmake_minimum_required(VERSION 4.1)
project(Light)

include(${CMAKE_CURRENT_SOURCE_DIR}/tools/cmake/functions.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/tools/cmake/definitions.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/tools/cmake/options.cmake)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/modules)
