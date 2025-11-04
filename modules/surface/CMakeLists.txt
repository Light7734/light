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
        platform_linux.cpp)
    target_link_libraries(surface PRIVATE X11)

else(WIN32)
    add_library_module(
        NAME
        surface
        INTERFACES
        system.cppm
        requests.cppm
        system.cppm
        requests.cppm
        events.cppm
        components.cppm
        SOURCES
        platform_windows.cpp)

endif()

target_link_libraries(
    surface
    PUBLIC ecs app math memory tbb
    PRIVATE logger lt_debug time)

add_test_module(surface system.test.cpp)

# add_fuzz_module(surface system.fuzz.cpp)
