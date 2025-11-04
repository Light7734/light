add_library_module(
    NAME
    app
    INTERFACES
    application.cppm
    system.cppm
    SOURCES
    entrypoint.cpp)

target_link_libraries(
    app
    PUBLIC memory
    PRIVATE lt_debug)
