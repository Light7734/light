add_library_module(NAME camera INTERFACES components.cppm)

target_link_libraries(camera PUBLIC math)
