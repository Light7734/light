add_library_module(
    NAME
    test
    INTERFACES
    test.cppm
    expects.cppm
    PRIVATE_INTERFACES
    registry.cppm
    SOURCES
    entrypoint.cpp
    DEPENDENCIES
    logger
)

add_library_module(NAME logger INTERFACES logger.cppm)

add_library_module(NAME bitwise INTERFACES operations.cppm)

add_library_module(NAME env INTERFACES constants.cppm)

add_library_module(
    NAME memory INTERFACES null_on_move.cppm reference.cppm scope.cppm
)

add_library_module(NAME time INTERFACES timer.cppm)

add_library_module(
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

add_library_module(
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

add_library_module(
    NAME
    assets
    INTERFACES
    shader.cppm
    metadata.cppm
    DEPENDENCIES
    logger
    lt_debug
)

add_library_module(
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

add_library_module(NAME camera INTERFACES components.cppm DEPENDENCIES math)

add_library_module(
    NAME
    app
    INTERFACES
    application.cppm
    system.cppm
    SOURCES
    entrypoint.cpp
    DEPENDENCIES
    memory
    PRIVATE_DEPENDENCIES
    lt_debug
)

add_library_module(
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

if(NOT WIN32)
    add_library_module(
        NAME
        surface
        INTERFACES
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
        tbb
        PRIVATE_DEPENDENCIES
        X11
        logger
        lt_debug
        time
    )
else()

endif()

add_library_module(
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

add_library_module(
    NAME
    renderer
    INTERFACES
    data.cppm
    frontends.cppm
    factory.cppm
    vk/api_wrapper.cppm
    vk/device.cppm
    vk/gpu.cppm
    vk/instance.cppm
    vk/surface.cppm
    vk/swapchain.cppm
    vk/buffer.cppm
    vk/pass.cppm
    DEPENDENCIES
    app
    ecs
    memory
    assets
    time
    bitwise
    camera
    PRIVATE_DEPENDENCIES
    surface
)

# add_subdirectory(./mirror)
