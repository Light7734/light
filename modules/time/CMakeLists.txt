add_library_module(time timer.cpp)
target_link_libraries(time PUBLIC tbb)
add_test_module(time timer.test.cpp)
