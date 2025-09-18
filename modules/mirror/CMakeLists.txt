add_library_module(libmirror 
)
target_link_libraries(
  libmirror
  INTERFACE
  app
  time
  input 
  surface
)

add_test_module(libmirror 
    layers/editor_layer.test.cpp
    panels/asset_browser.test.cpp
    panels/properties.test.cpp
    panels/scene_hierarchy.test.cpp
)

add_executable_module(mirror entrypoint/mirror.cpp)
target_link_libraries(mirror PRIVATE libmirror input)
