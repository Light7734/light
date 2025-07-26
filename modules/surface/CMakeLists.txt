if (NOT WIN32)
    add_library_module(surface system.cpp linux/system.cpp)
else()
endif()

target_link_libraries(surface PUBLIC 
    ecs
    app
    PRIVATE
    glfw
    logger 
    lt_debug
)
