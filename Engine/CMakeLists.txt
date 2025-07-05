cmake_minimum_required(VERSION 3.16)

if(CMAKE_COMPILER_IS_GNUCC)
  add_compile_options(-w)
endif()

if(MSVC)
  add_compile_options(/MP)
  add_compile_options(/W0)
endif()

file(GLOB_RECURSE ENGINE_ALL_FILES true ABSOLUTE ${ENGINE_DIR}src/*)
file(GLOB_RECURSE ENGINE_RES_FILES true ABSOLUTE ${ENGINE_DIR}res/*)
list(LENGTH ENGINE_ALL_FILES ENGINE_ALL_FILES_COUNT)

if(NOT WIN32)
  set(DX_DIR ${ENGINE_DIR}src/Platform/GraphicsAPI/DirectX/)
  set(WIN_DIR ${ENGINE_DIR}src/Platform/OS/Windows/)

  list(
    REMOVE_ITEM ENGINE_ALL_FILES
    ${DX_DIR}dxBlender.cpp
    ${DX_DIR}dxBuffers.cpp
    ${DX_DIR}dxFramebuffer.cpp
    ${DX_DIR}dxGraphicsContext.cpp
    ${DX_DIR}dxRenderCommand.cpp
    ${DX_DIR}dxShader.cpp
    ${DX_DIR}dxSharedContext.cpp
    ${DX_DIR}dxTexture.cpp
    ${DX_DIR}dxUserInterface.cpp
    ${DX_DIR}dxVertexLayout.cpp
    ${WIN_DIR}wWindow.cpp
  )
else()
  file(GLOB_RECURSE HLSL_FILES true ABSOLUTE ${ENGINE_DIR}res/*.hlsl)
  set_source_files_properties(${HLSL_FILES} PROPERTIES VS_TOOL_OVERRIDE "None")
endif()

list(LENGTH ENGINE_ALL_FILES ENGINE_ALL_FILES_COUNT)

include_directories(
  ${ENGINE_DIR}src/Engine/
  ${ENGINE_DIR}src/Platform/GraphicsAPI/
  ${ENGINE_DIR}src/Platform/OS/
  ${DEPENDENCIES_DIR}GLAD/include/
  ${DEPENDENCIES_DIR}GLFW/include/
  ${DEPENDENCIES_DIR}glm/
  ${DEPENDENCIES_DIR}imgui/
  ${DEPENDENCIES_DIR}spdlog/include/
  ${DEPENDENCIES_DIR}stb_image/
  ${DEPENDENCIES_DIR}yaml-cpp/include/
  ${DEPENDENCIES_DIR}shaderc/libshaderc/include
)

source_group(TREE ${ENGINE_DIR} FILES ${ENGINE_ALL_FILES} ${ENGINE_RES_FILES})
add_library(Engine STATIC ${ENGINE_ALL_FILES} ${ENGINE_RES_FILES})
