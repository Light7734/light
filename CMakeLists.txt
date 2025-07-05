cmake_minimum_required(VERSION 4.0)


project(Light)
set(CMAKE_CXX_STANDARD 20)

# directories
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_EXPORT_COMPILE_COMMANDS True)

set(MIRROR_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Mirror/)
set(ENGINE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Engine/)
set(DEPENDENCIES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/)

if(NOT MSV)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-error")
endif()

if(WIN32)
  add_compile_definitions(LIGHT_PLATFORM_WINDOWS)
elseif(UNIX)
  add_compile_definitions(LIGHT_PLATFORM_LINUX)
endif()

# Projects
add_subdirectory(${ENGINE_DIR}/)
add_subdirectory(${MIRROR_DIR}/)

# Dependencies
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)
find_package(spdlog REQUIRED)
find_package(stb REQUIRED)
find_package(yaml-cpp REQUIRED)
find_package(EnTT REQUIRED)
find_package(opengl_system REQUIRED)

add_subdirectory(${DEPENDENCIES_DIR})
add_subdirectory(external/glad/)

# Link
target_link_libraries(
  imgui
  PUBLIC glad
  PUBLIC opengl::opengl
  PUBLIC glm::glm 
  PUBLIC glfw
)

target_link_libraries(
  Engine
  PUBLIC glad
  PUBLIC opengl::opengl
  PUBLIC glfw
  PUBLIC spdlog::spdlog
  PUBLIC imgui
  PUBLIC stb::stb
  PUBLIC yaml-cpp::yaml-cpp
  PUBLIC EnTT::EnTT
)

target_link_libraries(
  Mirror
  PRIVATE Engine
  PRIVATE opengl::opengl
  PRIVATE imgui
)

# Precompiled headers
target_precompile_headers(Engine PUBLIC ${ENGINE_DIR}src/Engine/ltpch.hpp)

if(MSVC)
  set_property(DIRECTORY ${CMAE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Mirror)
endif()


set(CMAKE_BUILD_TYPE debug)
set(CMAKE_EXPORT_COMPILE_COMMANDS_ON)
