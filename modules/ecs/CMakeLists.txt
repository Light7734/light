add_library_module(ecs entity.cpp scene.cpp uuid.cpp serializer.cpp)
target_link_libraries(ecs 
    PUBLIC logger lt_debug EnTT::EnTT renderer input camera
    PRIVATE yaml-cpp::yaml-cpp asset_manager
)
