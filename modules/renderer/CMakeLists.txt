add_library_module(renderer
    blender.cpp
    buffers.cpp
    framebuffer.cpp
    graphics_context.cpp
    render_command.cpp
    renderer.cpp
    shader.cpp
    texture.cpp
    vertex_layout.cpp
    programs/quad.cpp
    programs/texture.cpp
    programs/tinted_texture.cpp
    gl/blender.cpp
    gl/buffers.cpp
    gl/framebuffers.cpp
    gl/graphics_context.cpp
    gl/render_command.cpp
    gl/shader.cpp
    gl/texture.cpp
    gl/vertex_layout.cpp
)

target_link_libraries(
  renderer
  PUBLIC camera
  PUBLIC input
  PUBLIC glad
  PUBLIC logger
  PUBLIC opengl::opengl
  PUBLIC glfw
  PUBLIC imgui
  PUBLIC asset_parser
  PUBLIC yaml-cpp::yaml-cpp
  PUBLIC EnTT::EnTT
  PRIVATE lt_debug 
)
