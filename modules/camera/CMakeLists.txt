add_library_module(camera camera.cpp ortho.cpp scene.cpp)

target_link_libraries(camera PUBLIC glm::glm)
