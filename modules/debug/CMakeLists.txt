add_library_module(lt_debug)
target_link_libraries(lt_debug INTERFACE logger)
target_precompile_headers(lt_debug INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/src/pch.hpp)
