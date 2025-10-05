add_library_module(renderer
    system.cpp

    # Vulkan - backend
    backend/vk/messenger.cpp
    backend/vk/context/context.cpp
    backend/vk/context/device.cpp
    backend/vk/context/gpu.cpp
    backend/vk/context/instance.cpp
    backend/vk/context/surface.cpp
    backend/vk/context/swapchain.cpp
    backend/vk/renderer/pass.cpp
    backend/vk/renderer/renderer.cpp

    # Vulkan - frontend
    frontend/messenger.cpp
    frontend/context/context.cpp
    frontend/renderer/renderer.cpp
)

target_link_libraries(renderer
PUBLIC 
    app 
    ecs
    memory
    assets
    time
    bitwise
PRIVATE
    surface
    pthread
)

# add_test_module(renderer 
#     system.test.cpp
#     vk/test_utils.cpp
#     vk/debug/messenger.test.cpp
#     vk/context/instance.test.cpp
#     vk/context/surface.test.cpp
#     vk/context/device.test.cpp
#     vk/context/swapchain.test.cpp
#     vk/context/context.test.cpp
#     vk/renderer/pass.test.cpp
#     vk/renderer/renderer.test.cpp
#     vk/pipeline.test.cpp
# ) 
# target_link_libraries(renderer_tests
# PRIVATE
#     surface
#     pthread
# )
