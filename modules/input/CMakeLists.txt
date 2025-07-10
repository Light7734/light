add_library_module(input input.cpp)
target_link_libraries(input PUBLIC spdlog::spdlog glm::glm imgui logger)
