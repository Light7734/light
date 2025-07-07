cmake_minimum_required(VERSION 4.0)
project(Light)
set(CMAKE_CXX_STANDARD 23)

include(${CMAKE_CURRENT_SOURCE_DIR}/tools/cmake/macros.cmake)

if(WIN32)
  add_compile_definitions(LIGHT_PLATFORM_WINDOWS)
elseif(UNIX)
  add_compile_definitions(LIGHT_PLATFORM_LINUX)
endif()

find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)
find_package(spdlog REQUIRED)
find_package(stb REQUIRED)
find_package(yaml-cpp REQUIRED)
find_package(EnTT REQUIRED)
find_package(opengl_system REQUIRED)
find_package(nlohmann_json REQUIRED)
find_package(lz4 REQUIRED)

add_subdirectory(./modules)
add_subdirectory(./external)
