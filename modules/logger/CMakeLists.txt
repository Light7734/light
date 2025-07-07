add_library_module(logger logger.cpp)
target_link_libraries(logger PUBLIC spdlog::spdlog)
