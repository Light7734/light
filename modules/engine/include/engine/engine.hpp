#pragma once

// core
#include <engine/core/application.hpp>
#include <engine/core/window.hpp>

// camera
#include <engine/camera/camera.hpp>

// debug
#include <logger/logger.hpp>

// events
#include <engine/events/char.hpp>
#include <engine/events/event.hpp>
#include <engine/events/keyboard.hpp>
#include <engine/events/mouse.hpp>
#include <engine/events/window.hpp>

// graphics
#include <engine/graphics/framebuffer.hpp>
#include <engine/graphics/graphics_context.hpp>
#include <engine/graphics/renderer.hpp>
#include <engine/graphics/texture.hpp>

// input
#include <engine/input/input.hpp>
#include <engine/input/key_codes.hpp>
#include <engine/input/mouse_codes.hpp>

// layer
#include <engine/layer/layer.hpp>
#include <engine/layer/layer_stack.hpp>

// user interface
#include <engine/user_interface/user_interface.hpp>

// utility
#include <engine/utils/resource_manager.hpp>

// time
#include <engine/time/timer.hpp>

// base
#include <engine/base/base.hpp>

// third party
#include <imgui.h>

// scene
#include <engine/scene/components.hpp>
#include <engine/scene/entity.hpp>
#include <engine/scene/scene.hpp>

// entry point
#ifdef LIGHT_ENTRY_POINT
	#include <engine/base/entrypoint.hpp>
#endif
