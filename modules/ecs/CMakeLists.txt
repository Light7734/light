add_library_module(NAME ecs INTERFACES sparse_set.cppm registry.cppm
                   entity.cppm)
target_link_libraries(ecs PUBLIC logger lt_debug memory)

add_test_module(ecs sparse_set.test.cpp registry.test.cpp)
