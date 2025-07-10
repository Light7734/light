add_executable_module(mirror 
    editor_layer.cpp
    mirror.cpp
    panel/asset_browser.cpp
    panel/properties.cpp
    panel/scene_hierarchy.cpp
)

target_link_libraries(
  mirror
  PUBLIC engine
  PUBLIC opengl::opengl
  PUBLIC ui
  PUBLIC imgui
  PUBLIC input
)
