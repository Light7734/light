add_library_module(test test.cpp entrypoint.cpp)
add_library_module(fuzz_test test.cpp fuzz.cpp)

target_link_libraries(test PUBLIC tbb)
target_link_libraries(fuzz_test PUBLIC tbb)

add_test_module(test test.test.cpp)
