add_executable_module(
    asset_baker baker.cpp
)

target_link_libraries(
    asset_baker
    PRIVATE asset_parser
    PRIVATE stb::stb
    PRIVATE logger
)
