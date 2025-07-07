add_executable(
    AssetBaker 

    ${CMAKE_CURRENT_SOURCE_DIR}/AssetBaker.cpp
)

set_target_properties(
    AssetBaker PROPERTIES
    CXX_STANDARD 20
)

target_include_directories(
    AssetBaker
    PRIVATE ${CMAKE_SOURCE_DIR}/AssetParser/
    PRIVATE ${CMAKE_SOURCE_DIR}/Vendor/stb/
)

target_link_libraries(
    AssetBaker
    PRIVATE ${CONAN_LIBS}
    PRIVATE AssetParser
)
