if (NOT WIN32)
    add_library_module(surface linux/system.cpp)
else(WIN32)
    add_library_module(surface windows/system.cpp)
endif()

target_link_libraries(surface PUBLIC 
    ecs
    app
    PRIVATE
    glfw
    logger 
    lt_debug
)

add_test_module(surface system.test.cpp)
add_fuzz_module(surface system.fuzz.cpp)
