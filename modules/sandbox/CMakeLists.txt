add_executable(sandbox sandbox.cpp)
target_link_libraries(sandbox PRIVATE preliminary logger bitwise env memory time test math assets app ecs surface renderer input mirror)

