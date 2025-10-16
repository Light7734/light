add_library_module(test test.cpp entrypoint.cpp)
add_library_module(fuzz_test test.cpp fuzz.cpp)

target_link_libraries(test PUBLIC tbb logger)
target_link_libraries(fuzz_test PUBLIC tbb logger)

add_test_module(test test.test.cpp)
