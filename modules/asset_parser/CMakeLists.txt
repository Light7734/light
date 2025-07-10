add_library_module(asset_parser 
    parser.cpp
    assets/texture.cpp
    assets/text.cpp
)

target_link_libraries(
    asset_parser
    PUBLIC LZ4::lz4_static 
    PUBLIC nlohmann_json::nlohmann_json 
    PUBLIC logger
)
