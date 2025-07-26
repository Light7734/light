add_library_module(input input.cpp)
target_link_libraries(input PUBLIC surface math imgui::imgui logger)
