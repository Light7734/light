add_library_module(time timer.cpp)

add_executable(timer_tests ${CMAKE_CURRENT_SOURCE_DIR}/src/timer.tests.cpp)
target_include_directories(timer_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(timer_tests PRIVATE time test)

