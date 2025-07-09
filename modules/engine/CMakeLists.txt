cmake_minimum_required(VERSION 3.16)

if(NOT WIN32)
    add_library_module(engine 
        camera/camera.cpp
        camera/ortho.cpp
        camera/scene.cpp
        core/application.cpp
        core/uuid.cpp
        debug/exceptions.cpp
        debug/instrumentor.cpp
        graphics/blender.cpp
        graphics/buffers.cpp
        graphics/framebuffer.cpp
        graphics/graphics_context.cpp
        graphics/render_command.cpp
        graphics/renderer.cpp
        graphics/renderer_programs/quad.cpp
        graphics/renderer_programs/texture.cpp
        graphics/renderer_programs/tinted_texture.cpp
        graphics/shader.cpp
        graphics/texture.cpp
        graphics/vertex_layout.cpp
        input/input.cpp
        layer/layer.cpp
        layer/layer_stack.cpp
        platform/graphics/opengl/blender.cpp
        platform/graphics/opengl/buffers.cpp
        platform/graphics/opengl/framebuffers.cpp
        platform/graphics/opengl/graphics_context.cpp
        platform/graphics/opengl/render_command.cpp
        platform/graphics/opengl/shader.cpp
        platform/graphics/opengl/texture.cpp
        platform/graphics/opengl/user_interface.cpp
        platform/graphics/opengl/vertex_layout.cpp
        platform/os/linux/l_window.cpp
        scene/entity.cpp
        scene/scene.cpp
        time/timer.cpp
        user_interface/user_interface.cpp
        utils/resource_manager.cpp
        utils/serializer.cpp
        utils/stringifier.cpp
    )
else()
    add_library_module(engine 
        camera/camera.cpp
        camera/ortho.cpp
        camera/scene.cpp
        core/application.cpp
        core/uuid.cpp
        debug/exceptions.cpp
        debug/instrumentor.cpp
        graphics/blender.cpp
        graphics/buffers.cpp
        graphics/framebuffer.cpp
        graphics/graphics_context.cpp
        graphics/render_command.cpp
        graphics/renderer.cpp
        graphics/renderer_programs/quad.cpp
        graphics/renderer_programs/texture.cpp
        graphics/renderer_programs/tinted_texture.cpp
        graphics/shader.cpp
        graphics/texture.cpp
        graphics/vertex_layout.cpp
        input/input.cpp
        layer/layer.cpp
        layer/layer_stack.cpp
        platform/graphics/directx/blender.cpp
        platform/graphics/directx/buffers.cpp
        platform/graphics/directx/framebuffers.cpp
        platform/graphics/directx/graphics_context.cpp
        platform/graphics/directx/render_command.cpp
        platform/graphics/directx/shader.cpp
        platform/graphics/directx/texture.cpp
        platform/graphics/directx/user_interface.cpp
        platform/graphics/directx/vertex_layout.cpp
        platform/graphics/opengl/blender.cpp
        platform/graphics/opengl/buffers.cpp
        platform/graphics/opengl/framebuffers.cpp
        platform/graphics/opengl/graphics_context.cpp
        platform/graphics/opengl/render_command.cpp
        platform/graphics/opengl/shader.cpp
        platform/graphics/opengl/texture.cpp
        platform/graphics/opengl/user_interface.cpp
        platform/graphics/opengl/vertex_layout.cpp
        platform/os/windows/w_window.cpp
        scene/entity.cpp
        scene/scene.cpp
        time/timer.cpp
        user_interface/user_interface.cpp
        utils/resource_manager.cpp
        utils/serializer.cpp
        utils/stringifier.cpp
    )
endif()

target_link_libraries(
  engine
  PUBLIC glad
  PUBLIC logger
  PUBLIC opengl::opengl
  PUBLIC glfw
  PUBLIC imgui
  PUBLIC asset_parser
  PUBLIC yaml-cpp::yaml-cpp
  PUBLIC EnTT::EnTT
)

target_precompile_headers(engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/ltpch.hpp)
