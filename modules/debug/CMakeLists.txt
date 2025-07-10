add_library_module(lt_debug instrumentor.cpp)
target_link_libraries(lt_debug PUBLIC logger)
target_precompile_headers(lt_debug PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/pch.hpp)
