add_library_module(NAME lt_debug INTERFACES instrumentor.cppm assertions.cppm)
target_link_libraries(lt_debug PUBLIC logger)
