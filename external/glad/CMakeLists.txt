add_library(glad ${CMAKE_CURRENT_SOURCE_DIR}/src/gl.c)
target_include_directories(glad PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(glad PUBLIC opengl::opengl)
