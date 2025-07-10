add_library_module(base)

target_precompile_headers(base INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/src/pch.hpp)
