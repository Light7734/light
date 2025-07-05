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
	Scope<UserInterface> m_UserInterface;
	Scope<Renderer> m_Renderer;

protected:
	GraphicsAPI m_GraphicsAPI;
	Ref<SharedContext> m_SharedContext = nullptr;

public:
	static Scope<GraphicsContext> Create(GraphicsAPI api, GLFWwindow* windowHandle);

	GraphicsContext(const GraphicsContext&) = delete;
	GraphicsContext& operator=(const GraphicsContext&) = delete;

	virtual ~GraphicsContext();

	virtual void LogDebugData() = 0;

	static inline GraphicsAPI GetGraphicsAPI() { return s_Context->m_GraphicsAPI; }
	static inline Ref<SharedContext> GetSharedContext() { return s_Context->m_SharedContext; }

	inline Renderer* GetRenderer() { return m_Renderer.get(); }
	inline UserInterface* GetUserInterface() { return m_UserInterface.get(); }

protected:
	GraphicsContext() = default;
};

} // namespace Light
