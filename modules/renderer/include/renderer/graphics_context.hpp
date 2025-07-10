#pragma once

struct GLFWwindow;

namespace Light {

class SharedContext;
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
	static auto create(
	    GraphicsAPI api,
	    GLFWwindow *window_handle

	) -> Scope<GraphicsContext>;

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

protected:
	GraphicsContext() = default;

	GraphicsAPI m_graphics_api;

	Ref<SharedContext> m_shared_context = nullptr;

private:
	static GraphicsContext *s_context;
};

} // namespace Light
