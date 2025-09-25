add_library_module(renderer
    system.cpp
    vk/context/instance.cpp
    vk/context/surface.cpp
    vk/context/device.cpp
    vk/context/swapchain.cpp
    vk/context/context.cpp
    vk/pipeline.cpp
)

target_link_libraries(renderer
PUBLIC 
    app 
    ecs
PRIVATE
    surface
    pthread
)

add_test_module(renderer 
    system.test.cpp
    vk/context/instance.test.cpp
    vk/context/surface.test.cpp
    vk/context/device.test.cpp
    vk/context/swapchain.test.cpp
    vk/context/context.test.cpp
    vk/pipeline.test.cpp
) 
