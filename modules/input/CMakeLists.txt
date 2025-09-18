add_library_module(input system.cpp)
target_link_libraries(input PUBLIC surface math  logger)

add_test_module(input system.test.cpp)
