add_library_module(universal_pch)
target_precompile_headers(universal_pch INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/public/pch/pch.hpp)
