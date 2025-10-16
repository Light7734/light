add_library(std INTERFACE)
target_precompile_headers(std INTERFACE
                          ${CMAKE_CURRENT_SOURCE_DIR}/public/pch.hpp)
