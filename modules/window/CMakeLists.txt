if (NOT WIN32)
    add_library_module(window linux/window.cpp)
else()
    add_library_module(window windows/window.cpp)
endif()

target_link_libraries(window PUBLIC 
    glm::glm

    PRIVATE
    glfw
    logger 
    lt_debug
    input
)
