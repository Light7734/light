add_library_module(ui ui.cpp gl/ui.cpp)
target_link_libraries(ui PUBLIC spdlog::spdlog imgui renderer logger lt_debug)
