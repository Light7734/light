add_library(preliminary INTERFACE)
target_precompile_headers(preliminary INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/src/pch.hpp)
target_include_directories(preliminary INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include/)
