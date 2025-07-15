add_library_module(test test.cpp entrypoint.cpp)

add_executable(test_tests ${CMAKE_CURRENT_SOURCE_DIR}/tests/test.cpp)
target_link_libraries(test_tests PRIVATE test)
