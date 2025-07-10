if(NOT WIN32)
    add_library_module(engine 
        core/application.cpp
        core/uuid.cpp
        debug/exceptions.cpp
        debug/instrumentor.cpp
        layer/layer.cpp
        layer/layer_stack.cpp
        os/linux/l_window.cpp
        scene/entity.cpp
        scene/scene.cpp
        time/timer.cpp
        utils/serializer.cpp
    )
else()
    add_library_module(engine 
        core/application.cpp
        core/uuid.cpp
        debug/exceptions.cpp
        debug/instrumentor.cpp
        layer/layer.cpp
        layer/layer_stack.cpp
        os/windows/w_window.cpp
        scene/entity.cpp
        scene/scene.cpp
        time/timer.cpp
        utils/serializer.cpp
    )
endif()

target_link_libraries(
  engine
  PUBLIC renderer
  PUBLIC glad
  PUBLIC logger
  PUBLIC opengl::opengl
  PUBLIC glfw
  PUBLIC ui
  PUBLIC asset_parser
  PUBLIC asset_manager
  PUBLIC yaml-cpp::yaml-cpp
  PUBLIC EnTT::EnTT
  PUBLIC lt_debug 
)
