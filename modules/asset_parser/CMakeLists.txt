add_library(AssetParser 
    ${CMAKE_CURRENT_SOURCE_DIR}/AssetParser.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/TextureAsset.cpp
)

target_include_directories(
    AssetParser
    PRIVATE ${CMAKE_SOURCE_DIR}/Vendor/nlohmann/single_include
    PRIVATE ${CMAKE_SOURCE_DIR}/Vendor/lz4/lib/
)

target_link_libraries(
    AssetParser
    PRIVATE lz4_static
    PRIVATE nlohmann_json::nlohmann_json
)
