add_library_module(
    renderer
    system.cpp
    # Vulkan - backend
    backend/vk/messenger.cpp
    backend/vk/context/device.cpp
    backend/vk/context/gpu.cpp
    backend/vk/context/instance.cpp
    backend/vk/context/surface.cpp
    backend/vk/context/swapchain.cpp
    backend/vk/renderer/pass.cpp
    backend/vk/renderer/renderer.cpp
    # Vulkan - frontend
    frontend/messenger.cpp
    frontend/context/device.cpp
    frontend/context/gpu.cpp
    frontend/context/instance.cpp
    frontend/context/surface.cpp
    frontend/context/swapchain.cpp
    frontend/renderer/renderer.cpp
    frontend/renderer/pass.cpp)

target_link_libraries(
    renderer
    PUBLIC app ecs memory assets time bitwise
    PRIVATE surface pthread)

add_test_module(
    renderer
    test/utils.cpp
    system.test.cpp
    # general backend tests through the frontend
    frontend/messenger.test.cpp
    frontend/context/surface.test.cpp
    frontend/context/device.test.cpp
    frontend/context/swapchain.test.cpp
    frontend/renderer/pass.test.cpp
    frontend/renderer/renderer.test.cpp
    # backend specific tests -- vk
    backend/vk/context/instance.test.cpp
    # backend specific tests -- dx backend specific tests -- mt
)

target_link_libraries(renderer_tests PRIVATE surface pthread)
