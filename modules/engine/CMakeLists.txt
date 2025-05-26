add_executable(engine ${CMAKE_CURRENT_SOURCE_DIR}/private/entrypoint.cpp)
target_link_libraries(engine  PRIVATE pch)
