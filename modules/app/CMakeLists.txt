add_library_module(app application.cpp)
target_link_libraries(
    app
    PUBLIC memory
    PRIVATE lt_debug)
