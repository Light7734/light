add_library_module(asset_parser 
    parser.cpp
    assets/texture.cpp
)

target_link_libraries(
    asset_parser
    PRIVATE LZ4::lz4_static 
    PRIVATE nlohmann_json::nlohmann_json 
)
