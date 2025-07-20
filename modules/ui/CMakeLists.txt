add_library_module(ui ui.cpp gl/ui.cpp gl/backend.cpp glfw/glfw.cpp)
target_link_libraries(ui PUBLIC imgui renderer logger lt_debug)
