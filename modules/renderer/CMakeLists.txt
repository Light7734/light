add_library_module(
    NAME
    renderer
    INTERFACES
    # system.cppm Vulkan - backend
    api.cppm
    frontends.cppm
    factory.cppm
    # backends/vk/messenger.cppm backends/vk/library_loader.cppm
    backends/vk/library_wrapper.cppm
    backends/vk/context/device.cppm
    backends/vk/context/gpu.cppm
    backends/vk/context/instance.cppm
    backends/vk/context/surface.cppm
    # backends/vk/context/swapchain.cppm backends/vk/data/buffer.cppm
    # backends/vk/renderer/pass.cppm backends/vk/renderer/renderer.cppm frontend
    # frontend/messenger.cppm frontend/context/device.cppm
    # frontend/context/gpu.cppm frontend/context/instance.cppm
    # frontend/context/surface.cppm frontend/context/swapchain.cppm
    # frontend/data/buffer.cppm frontend/renderer/renderer.cppm
    # frontend/renderer/pass.cppm
)

target_link_libraries(
    renderer
    PUBLIC app
           ecs
           memory
           assets
           time
           bitwise
           camera
    PRIVATE surface pthread)

return()

add_test_module(
    renderer
    test/utils.cpp
    system.test.cpp
    # general backend tests through the frontend
    frontend/messenger.test.cpp
    frontend/context/surface.test.cpp
    frontend/context/device.test.cpp
    frontend/context/swapchain.test.cpp
    frontend/data/buffer.test.cpp
    # frontend/renderer/pass.test.cpp
    frontend/renderer/renderer.test.cpp
    # backend specific tests -- vk
    backend/vk/context/instance.test.cpp)

target_link_libraries(renderer_tests PRIVATE surface pthread)
