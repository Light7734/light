add_library_module(NAME libasset_baker INTERFACES bakers.cppm)
target_link_libraries(libasset_baker PUBLIC assets logger lt_debug)

add_executable(asset_baker entrypoint.cpp)
target_link_libraries(asset_baker PRIVATE libasset_baker)
