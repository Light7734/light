add_library_module(ecs entity.cpp scene.cpp uuid.cpp)
target_link_libraries(ecs PUBLIC logger lt_debug EnTT::EnTT camera math)
