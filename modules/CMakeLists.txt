add_module(NAME preliminary INTERFACES module.cppm fundumental_types.cppm assertions.cppm build_constants.cppm)
add_module(NAME logger INTERFACES logger.cppm TESTS logger.test.cpp DEPENDENCIES preliminary)
add_module(NAME tracer INTERFACES tracer.cppm DEPENDENCIES preliminary logger)

add_module(NAME bitwise INTERFACES operations.cppm DEPENDENCIES preliminary)
add_module(NAME memory INTERFACES null_on_move.cppm reference.cppm scope.cppm
    DEPENDENCIES
    preliminary
    logger
)
add_module(NAME time INTERFACES timer.cppm TESTS timer.test.cpp DEPENDENCIES preliminary)

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
    preliminary
    logger
    TESTS
    test.test.cpp
)

add_module(
    NAME
    math
    INTERFACES
    algebra.cppm
    trig.cppm
    vec2.cppm
    vec3.cppm
    vec4.cppm
    mat4.cppm
    components.cppm
    DEPENDENCIES
    preliminary
)

add_module(
    NAME
    assets
    INTERFACES
    shader.cppm
    metadata.cppm
    DEPENDENCIES
    preliminary
    logger
    TESTS
    shader.test.cpp
)

add_module(
    NAME
    asset_baker
    ROOT_DIR
    ${CMAKE_CURRENT_SOURCE_DIR}/asset_baker
    INTERFACES
    bakers.cppm
    ENTRYPOINT
    entrypoint.cpp
    DEPENDENCIES
    preliminary
    assets
    logger
)

# add_executable(asset_baker entrypoint.cpp) target_link_libraries(asset_baker
# PRIVATE libasset_baker)

add_module(NAME camera INTERFACES components.cppm DEPENDENCIES preliminary math)

add_module(
    NAME
    app
    INTERFACES
    application.cppm
    system.cppm
    DEPENDENCIES
    preliminary
    memory
    PRIVATE_DEPENDENCIES
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
    memory
    TESTS
    registry.test.cpp
    sparse_set.test.cpp
)

add_module(NAME input_codes INTERFACES input_codes.cppm DEPENDENCIES preliminary)

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
        DEPENDENCIES
        preliminary
        ecs
        app
        math
        memory
        input_codes
        PRIVATE_DEPENDENCIES
        logger
        time
        TESTS
        system.test.cpp
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
        DEPENDENCIES
        preliminary
        ecs
        app
        math
        memory
        input_codes
        wayland-client
        PRIVATE_DEPENDENCIES
        X11
        logger
        time
        TESTS
        system.test.cpp
    )

function(add_wayland_protocol_target TARGET_NAME SPEC NAME)
    add_custom_target(wayland_${TARGET_NAME}_header COMMAND wayland-scanner client-header /usr/share/wayland-protocols${SPEC} ${CMAKE_CURRENT_SOURCE_DIR}/surface/wayland-protocols/${NAME}.h)
    add_dependencies(surface wayland_${TARGET_NAME}_header)
    add_custom_target(wayland_${TARGET_NAME}_source COMMAND wayland-scanner private-code /usr/share/wayland-protocols${SPEC} ${CMAKE_CURRENT_SOURCE_DIR}/surface/wayland-protocols/${NAME}.c)
    add_dependencies(surface wayland_${TARGET_NAME}_source)

    target_sources(surface PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/surface/wayland-protocols/${NAME}.c)
endfunction()

target_include_directories(surface PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/surface/wayland-protocols/)
add_wayland_protocol_target(xdg_shell "/stable/xdg-shell/xdg-shell.xml" xdg-shell)

else()
    message(FATAL "Failed to generate cmake: unsupported platform")

endif()

add_module(
    NAME
    input
    INTERFACES
    system.cppm
    components.cppm
    events.cppm
    DEPENDENCIES
    preliminary
    input_codes
    surface
    math
    logger
    TESTS
    system.test.cpp
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
    preliminary
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
    TESTS
    _tests/buffer.cpp
    _tests/debugger.cpp
    _tests/device.cpp
    _tests/pass.cpp
    _tests/renderer.cpp
    _tests/surface.cpp
    _tests/system.cpp
    TEST_INTERFACES
    _tests/utils.cppm
)

add_module(
    NAME
    mirror
    ROOT_DIR
    ${CMAKE_CURRENT_SOURCE_DIR}/mirror
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
)

if(ENABLE_SANDBOX)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/sandbox/)
endif()
