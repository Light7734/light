# GLAD #
add_subdirectory(./glad)

set(MIRROR_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../modules/mirror/)
set(DEPENDENCIES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/)

if (CMAKE_COMPILER_IS_GNUCC)
    add_compile_options(-w)
endif()
if(MSVC)
    add_compile_options(/MP)
    add_compile_options(/W0)
endif()

file(GLOB IMGUI_FILES true ABSOLUTE
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui_tables.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui_widgets.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui_draw.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui_demo.cpp
)

set(BACKENDS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends/)


file(GLOB IMGUI_BACKEND_FILES true ABSOLUTE 
    ${BACKENDS_DIR}imgui_impl_opengl3.cpp
    ${BACKENDS_DIR}imgui_impl_glfw.cpp
    # ${BACKENDS_DIR}imgui_impl_vulkan.cpp ${BACKENDS_DIR}imgui_impl_vulkan.h
)

if(WIN32)
    file(GLOB IMGUI_WINDOWS_BACKEND_FILES true ABSOLUTE ${CMAKE_CURRENT_SOURCE_DIR}/backends/
    ${BACKENDS_DIR}imgui_impl_dx11.cpp
    ${BACKENDS_DIR}imgui_impl_win32.cpp
)

    list(APPEND IMGUI_BACKEND_FILES ${IMGUI_WINDOWS_BACKEND_FILES})
endif()

add_compile_definitions(IMGUI_IMPL_OPENGL_LOADER_GLAD)
include_directories(${DEPENDENCIES_DIR}GLFW/include)
include_directories(${DEPENDENCIES_DIR}glm/)

add_library(imgui STATIC ${IMGUI_FILES} ${IMGUI_BACKEND_FILES})

target_include_directories(imgui PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/imgui)
target_link_libraries(
  imgui
  PUBLIC glad
  PUBLIC opengl::opengl
  PUBLIC glm::glm 
  PUBLIC glfw
)

# Copy imconfig.h over
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/configurations/imgui/imconfig.h
    DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/imgui/)
