add_library_module(ecs sparse_set.cpp)
target_link_libraries(ecs PUBLIC logger lt_debug memory)

add_test_module(ecs sparse_set.test.cpp registry.test.cpp)
