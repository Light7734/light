add_library_module(NAME assets INTERFACES shader.cppm metadata.cppm)
target_link_libraries(assets PUBLIC logger lt_debug)
add_test_module(assets shader.test.cpp)
