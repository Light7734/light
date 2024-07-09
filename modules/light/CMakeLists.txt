add_executable(light ${CMAKE_CURRENT_SOURCE_DIR}/src/entrypoint.cpp)

target_link_libraries(light PRIVATE preliminary)
