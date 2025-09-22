add_library_module(renderer
    system.cpp
    vk/context.cpp
)

target_link_libraries(renderer
PUBLIC 
    app 
    ecs
    vulkan
    memory
    surface
)

add_test_module(renderer 
    system.test.cpp
) 
