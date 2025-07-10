#pragma once

// core
#include <engine/core/application.hpp>
#include <engine/core/window.hpp>

// debug
#include <logger/logger.hpp>

// graphics
#include <renderer/framebuffer.hpp>
#include <renderer/graphics_context.hpp>
#include <renderer/renderer.hpp>
#include <renderer/texture.hpp>

// layer
#include <engine/layer/layer.hpp>
#include <engine/layer/layer_stack.hpp>

// time
#include <engine/time/timer.hpp>

// base


// third party
#include <imgui.h>

// entry point
#ifdef LIGHT_ENTRY_POINT
	#include <engine/core/entrypoint.hpp>
#endif
