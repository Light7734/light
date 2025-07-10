add_library_module(asset_manager 
    asset_manager.cpp
)

target_link_libraries(
  asset_manager
  PUBLIC asset_parser
  PRIVATE renderer
)
