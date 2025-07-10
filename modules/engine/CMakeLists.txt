if(NOT WIN32)
    add_library_module(engine 
        core/application.cpp
        layer/layer.cpp
        layer/layer_stack.cpp
        time/timer.cpp
        utils/serializer.cpp
    )
else()
    add_library_module(engine 
        core/application.cpp
        layer/layer.cpp
        layer/layer_stack.cpp
        time/timer.cpp
        utils/serializer.cpp
    )
endif()

target_link_libraries(engine 
PUBLIC 
    renderer
    logger
    ui
    asset_parser
    asset_manager
    lt_debug 
    ecs 
    window

    glad

    opengl::opengl
    yaml-cpp::yaml-cpp
    EnTT::EnTT
)
