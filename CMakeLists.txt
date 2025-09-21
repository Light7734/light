cmake_minimum_required(VERSION 3.14)
project(Light)

include(${CMAKE_CURRENT_SOURCE_DIR}/tools/cmake/functions.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/tools/cmake/definitions.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/tools/cmake/options.cmake)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/modules)
