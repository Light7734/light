add_executable_module(
    asset_baker entrypoint/baker.cpp
)

target_link_libraries(
    asset_baker
    PRIVATE asset_parser
    PRIVATE logger
)
