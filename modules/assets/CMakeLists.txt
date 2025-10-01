add_library_module(assets 
    shader.cpp
)

target_link_libraries(
assets 
PUBLIC
logger 
lt_debug
)

add_test_module(assets
    shader.test.cpp
)
