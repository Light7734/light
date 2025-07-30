add_library_module(test test.cpp entrypoint.cpp)
add_library_module(fuzz_test test.cpp fuzz.cpp)

add_test_module(test test.test.cpp)
