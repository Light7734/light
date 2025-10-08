add_library_module(libasset_baker
    bakers.cpp
)
target_link_libraries(libasset_baker
PUBLIC
    assets
    logger
    lt_debug
    tbb
)
add_test_module(libasset_baker 
    bakers.test.cpp
)

add_executable_module(asset_baker
    entrypoint/baker.cpp
)
target_link_libraries(asset_baker PRIVATE libasset_baker)
