#pragma once

#include <engine/base/base.hpp>

struct GLFWwindow;

namespace Light {

class Renderer;
class resource_manager;
class SharedContext;
class UserInterface;
class WindowResizedEvent;

enum class GraphicsAPI
{
	Default = 0,
	OpenGL,
	DirectX,
	Vulkan,
	Metal
};

class GraphicsContext
{
public:
	static auto create(GraphicsAPI api, GLFWwindow *windowHandle) -> Scope<GraphicsContext>;

	GraphicsContext(const GraphicsContext &) = delete;

	GraphicsContext &operator=(const GraphicsContext &) = delete;

	virtual ~GraphicsContext();

	virtual void log_debug_data() = 0;

	static GraphicsAPI get_graphics_api()
	{
		return s_context->m_graphics_api;
	}

	static Ref<SharedContext> get_shared_context()
	{
		return s_context->m_shared_context;
	}

	auto get_renderer() -> Renderer *
	{
		return m_renderer.get();
	}

	auto get_user_interface() -> UserInterface *
	{
		return m_user_interface.get();
	}

protected:
	GraphicsContext() = default;

	GraphicsAPI m_graphics_api;

	Ref<SharedContext> m_shared_context = nullptr;

private:
	static GraphicsContext *s_context;

	Scope<UserInterface> m_user_interface;

	Scope<Renderer> m_renderer;
};

} // namespace Light
