add_executable(sandbox sandbox.cpp)
target_link_libraries(sandbox PRIVATE logger bitwise env memory time test lt_debug math assets app ecs surface renderer input mirror)

