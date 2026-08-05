add_module(
    NAME
    preliminary
    INTERFACES
    concepts.cppm
    module.cppm
    fundumental_types.cppm
    assertions.cppm
    build_constants.cppm
)
add_module(
    NAME
    logger
    INTERFACES
    logger.cppm
    TESTS
    logger.test.cpp
    DEPENDENCIES
    preliminary
)
add_module(
    NAME
    tracer
    INTERFACES
    tracer.cppm
    DEPENDENCIES
    preliminary
    logger
)

add_module(NAME bitwise INTERFACES operations.cppm DEPENDENCIES preliminary)
add_module(
    NAME
    memory
    INTERFACES
    not_null.cppm
    null_on_move.cppm
    reference.cppm
    scope.cppm
    DEPENDENCIES
    preliminary
    logger
    TESTS
    not_null.test.cpp
)
add_module(
    NAME
    time
    INTERFACES
    timer.cppm
    TESTS
    timer.test.cpp
    DEPENDENCIES
    preliminary
)

add_module(
    NAME
    test
    INTERFACES
    module.cppm
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
    formatter.cppm
    DEPENDENCIES
    preliminary
    TESTS
    trig.test.cpp
    vec2.test.cpp
    vec3.test.cpp
    vec4.test.cpp
    mat4.test.cpp
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

add_module(
    NAME
    camera
    INTERFACES
    components.cppm
    DEPENDENCIES
    preliminary
    math
)

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

add_module(
    NAME input_codes INTERFACES input_codes.cppm DEPENDENCIES preliminary
)

if(ENABLE_MSAN OR ENABLE_TSAN)
    return()
endif()

add_custom_command(
    OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/surface/wayland-protocols/xdg-shell.h
           ${CMAKE_CURRENT_SOURCE_DIR}/surface/wayland-protocols/xdg-shell.c
    COMMAND
        wayland-scanner client-header
        /usr/share/wayland-protocols/stable/xdg-shell/xdg-shell.xml
        ${CMAKE_CURRENT_SOURCE_DIR}/surface/wayland-protocols/xdg-shell.h
    COMMAND
        wayland-scanner private-code
        /usr/share/wayland-protocols/stable/xdg-shell/xdg-shell.xml
        ${CMAKE_CURRENT_SOURCE_DIR}/surface/wayland-protocols/xdg-shell.c
    DEPENDS /usr/share/wayland-protocols/stable/xdg-shell/xdg-shell.xml
)
add_custom_target(
    xdg-shell-gen
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/surface/wayland-protocols/xdg-shell.h
            ${CMAKE_CURRENT_SOURCE_DIR}/surface/wayland-protocols/xdg-shell.c
)

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
    wayland-protocols/xdg-shell.c
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
target_include_directories(
    surface PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/surface/wayland-protocols/
)
add_dependencies(surface xdg-shell-gen)

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
    components.cppm
    api_wrapper.cppm
    device.cppm
    gpu.cppm
    instance.cppm
    surface.cppm
    swapchain.cppm
    buffer.cppm
    pass.cppm
    renderer.cppm
    debugger.cppm
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
    buffer.test.cpp
    debugger.test.cpp
    device.test.cpp
    pass.test.cpp
    renderer.test.cpp
    surface.test.cpp
    system.test.cpp
    TEST_INTERFACES
    test_utils.test.cppm
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
