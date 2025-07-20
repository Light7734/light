add_library_module(libmirror 
    layers/editor_layer.cpp
    panels/asset_browser.cpp
    panels/properties.cpp
    panels/scene_hierarchy.cpp
)
target_link_libraries(
  libmirror
  PUBLIC app
  PUBLIC opengl::opengl
  PUBLIC ui
  PUBLIC imgui
  PUBLIC input
)

add_test_module(libmirror 
    layers/editor_layer.test.cpp
    panels/asset_browser.test.cpp
    panels/properties.test.cpp
    panels/scene_hierarchy.test.cpp
)

add_executable_module(mirror entrypoint/mirror.cpp)
target_link_libraries(mirror PRIVATE libmirror)
