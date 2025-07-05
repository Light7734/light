#pragma once

#include <engine/base/base.hpp>

struct GLFWwindow;

namespace Light {

class renderer;
class resource_manager;
class SharedContext;

class UserInterface;

class WindowResizedEvent;

enum class GraphicsAPI
{
	Default = 0,
	OpenGL,
	DirectX,
	Vulkan, // :#todo
	Metal   // :#todo
};

class GraphicsContext /* singleton */
{
private:
	static GraphicsContext* s_Context;

private:
	Scope<UserInterface> m_user_interface;
	Scope<renderer> m_renderer;

protected:
	GraphicsAPI m_graphics_api;
	Ref<SharedContext> m_shared_context = nullptr;

public:
	static Scope<GraphicsContext> create(GraphicsAPI api, GLFWwindow* windowHandle);

	GraphicsContext(const GraphicsContext&) = delete;
	GraphicsContext& operator=(const GraphicsContext&) = delete;

	virtual ~GraphicsContext();

	virtual void log_debug_data() = 0;

	static inline GraphicsAPI get_graphics_api() { return s_Context->m_graphics_api; }
	static inline Ref<SharedContext> get_shared_context() { return s_Context->m_shared_context; }

	inline renderer* GetRenderer() { return m_renderer.get(); }
	inline UserInterface* GetUserInterface() { return m_user_interface.get(); }

protected:
	GraphicsContext() = default;
};

} // namespace Light
