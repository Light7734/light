add_module(
    NAME
    lsd
    INTERFACES
    lsd.cppm
    ref.cppm
    vec.cppm
    arr.cppm
    str.cppm
    set.cppm
    span.cppm
    hash.cppm
    utils.cppm
    scope.cppm
    bitwise.cppm
    thread.cppm
    primitives.cppm
    src_location.cppm
)
add_module(NAME logger INTERFACES logger.cppm DEPENDENCIES lsd)
add_module(
    NAME
    test
    INTERFACES
    test.cppm
    expects.cppm
    registry.cppm
    SOURCES
    entrypoint.cpp
    DEPENDENCIES
    lsd
    logger
)
return()
add_module(NAME env INTERFACES constants.cppm)
add_module(NAME memory INTERFACES null_on_move.cppm reference.cppm scope.cppm)
add_module(NAME time INTERFACES timer.cppm)

add_module(
    NAME
    lt_debug
    ROOT_DIR
    ${CMAKE_CURRENT_SOURCE_DIR}/debug
    INTERFACES
    instrumentor.cppm
    assertions.cppm
    DEPENDENCIES
    logger
)

add_module(
    NAME
    math
    INTERFACES
    algebra.cppm
    mat4.cppm
    trig.cppm
    vec2.cppm
    vec3.cppm
    vec4.cppm
    components.cppm
)

add_module(
    NAME
    assets
    INTERFACES
    shader.cppm
    metadata.cppm
    DEPENDENCIES
    logger
    lt_debug
)

add_module(
    NAME
    libasset_baker
    ROOT_DIR
    ${CMAKE_CURRENT_SOURCE_DIR}/asset_baker
    INTERFACES
    bakers.cppm
    DEPENDENCIES
    assets
    logger
    lt_debug
)

# add_executable(asset_baker entrypoint.cpp) target_link_libraries(asset_baker
# PRIVATE libasset_baker)

add_module(NAME camera INTERFACES components.cppm DEPENDENCIES math)

add_module(
    NAME
    app
    INTERFACES
    application.cppm
    system.cppm
    DEPENDENCIES
    memory
    PRIVATE_DEPENDENCIES
    lt_debug
)

add_module(
    NAME
    ecs
    INTERFACES
    sparse_set.cppm
    registry.cppm
    entity.cppm
    DEPENDENCIES
    logger
    lt_debug
    memory
)

if(WIN32)
    add_module(
        NAME
        surface
        INTERFACES
        constants.cppm
        system.cppm
        requests.cppm
        events.cppm
        components.cppm
        SOURCES
        platform_windows.cpp
        DEPENDENCIES
        ecs
        app
        math
        memory
        PRIVATE_DEPENDENCIES
        logger
        lt_debug
        time
    )

elseif(UNIX)
    add_module(
        NAME
        surface
        INTERFACES
        constants.cppm
        system.cppm
        requests.cppm
        events.cppm
        components.cppm
        SOURCES
        platform_linux.cpp
        DEPENDENCIES
        ecs
        app
        math
        memory
        PRIVATE_DEPENDENCIES
        X11
        logger
        lt_debug
        time
    )

else()
    message(FATAL "Failed to generate cmake: unsupported platform")

endif()

add_module(
    NAME
    input
    INTERFACES
    system.cppm
    codes.cppm
    components.cppm
    events.cppm
    DEPENDENCIES
    surface
    math
    logger
)

find_package(Vulkan REQUIRED)
message("Vulkan Libraries are: ${Vulkan_LIBRARIES}")
add_module(
    NAME
    renderer
    INTERFACES
    data.cppm
    system.cppm
    frontends.cppm
    components.cppm
    factory.cppm
    vk/api_wrapper.cppm
    vk/device.cppm
    vk/gpu.cppm
    vk/instance.cppm
    vk/surface.cppm
    vk/swapchain.cppm
    vk/buffer.cppm
    vk/pass.cppm
    vk/renderer.cppm
    vk/debugger.cppm
    DEPENDENCIES
    app
    ecs
    memory
    assets
    time
    bitwise
    camera
    ${Vulkan_LIBRARIES}
    Vulkan::Vulkan
    PRIVATE_DEPENDENCIES
    surface
)

add_module(
    NAME
    mirror
    ROOT_DIR
    ${CMAKE_CURRENT_SOURCE_DIR}/mirror
    ENTRYPOINT
    entrypoint.cpp
    INTERFACES
    system.cppm
    DEPENDENCIES
    memory
    app
    time
    input
    surface
    renderer
    camera
    TESTS
    system.test.cpp
)
