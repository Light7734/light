cmake_minimum_required(VERSION 4.0)


project(Light)
set(CMAKE_CXX_STANDARD 20)

# directories
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(MIRROR_DIR ${CMAKE_BINARY_DIR}/../Mirror/)
set(ENGINE_DIR ${CMAKE_BINARY_DIR}/../Engine/)
set(DEPENDENCIES_DIR ${CMAKE_BINARY_DIR}/../Dependencies/)

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
add_subdirectory(${DEPENDENCIES_DIR}GLAD/)
add_subdirectory(${DEPENDENCIES_DIR}GLFW/)
add_subdirectory(${DEPENDENCIES_DIR})
add_subdirectory(${DEPENDENCIES_DIR}spdlog/)
add_subdirectory(${DEPENDENCIES_DIR}glm/)
add_subdirectory(${DEPENDENCIES_DIR}entt/)
add_subdirectory(${DEPENDENCIES_DIR}stb_image/)
add_subdirectory(${DEPENDENCIES_DIR}yaml-cpp/)
add_subdirectory(${DEPENDENCIES_DIR}shaderc/)

# Link
target_link_libraries(
  imgui
  PUBLIC glad
  PUBLIC glfw
)

target_link_libraries(
  Engine
  PRIVATE glad
  PRIVATE glfw
  PRIVATE spdlog
  PRIVATE imgui
  PRIVATE stb_image
  PRIVATE yaml-cpp
  PRIVATE shaderc
)

target_link_libraries(
  Mirror
  PRIVATE Engine
  PRIVATE imgui
)

# Precompiled headers
target_precompile_headers(Engine PUBLIC ${ENGINE_DIR}src/Engine/ltpch.hpp)

if(MSVC)
  set_property(DIRECTORY ${CMAE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Mirror)
endif()


set(CMAKE_BUILD_TYPE debug)
set(CMAKE_EXPORT_COMPILE_COMMANDS_ON)
