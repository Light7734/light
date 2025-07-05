#pragma once

#include <engine/base/base.hpp>

struct GLFWwindow;

namespace Light {

class Renderer;
class ResourceManager;
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
	Scope<Renderer> m_renderer;

protected:
	GraphicsAPI m_graphics_api;
	Ref<SharedContext> m_shared_context = nullptr;

public:
	static Scope<GraphicsContext> Create(GraphicsAPI api, GLFWwindow* windowHandle);

	GraphicsContext(const GraphicsContext&) = delete;
	GraphicsContext& operator=(const GraphicsContext&) = delete;

	virtual ~GraphicsContext();

	virtual void LogDebugData() = 0;

	static inline GraphicsAPI GetGraphicsAPI() { return s_Context->m_graphics_api; }
	static inline Ref<SharedContext> GetSharedContext() { return s_Context->m_shared_context; }

	inline Renderer* GetRenderer() { return m_renderer.get(); }
	inline UserInterface* GetUserInterface() { return m_user_interface.get(); }

protected:
	GraphicsContext() = default;
};

} // namespace Light
