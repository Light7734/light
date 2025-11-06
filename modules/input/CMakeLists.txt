add_library_module(
    NAME
    input
    INTERFACES
    system.cppm
    codes.cppm
    components.cppm
    events.cppm)
target_link_libraries(input PUBLIC surface math logger)

# add_test_module(input system.test.cpp)
