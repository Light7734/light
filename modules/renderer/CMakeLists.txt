add_library_module(renderer
    system.cpp
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
    vk/instance.cpp
)

target_link_libraries(
  renderer
  PUBLIC camera
  PUBLIC input
  PUBLIC logger
  PUBLIC imgui
  PUBLIC asset_parser
  PUBLIC EnTT::EnTT
  PRIVATE lt_debug 
  PRIVATE window
  PUBLIC vulkan
)

add_test_module(renderer 
    system.test.cpp
) 
target_link_libraries(
  renderer_tests
  PRIVATE lt_debug 
  PRIVATE window
)
